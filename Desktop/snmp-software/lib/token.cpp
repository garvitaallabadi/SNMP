#include <iostream>
#include <string.h>
#include <pqxx/pqxx> 
#include <sstream>
#include "sha.h"
#include <time.h>


using namespace pqxx;


int strcmp_me(std::string str1, std::string str2)
{
	int i=0, diff =1;
	while(1)
	{
		if(str1[i]!=str2[i])
		{
			diff = 1;
			break;
		}
		if(str1[i] == '\0' && str2[i] == '\0')
		{
			diff=0;
			break;
		}
		i++;
	}
	if(diff==0) return 0;
	else return 1;
}

std::string generatetoken(std::string inpUsername,std::string inpPassword){
	char *sql,*sql2;
	std::string token;
	int alreadyExistsFlag=0;
	const char* inpU = inpUsername.c_str(); 
	try{
		connection C("dbname=snmpdb user=postgres password=harkirat \
	      	hostaddr=127.0.0.1 port=5432");
      		if (!C.is_open()) {
        		std::cout << "Can't open database" << std::endl;
      		}

		sql = (char*)"SELECT username,password from users";
		work W1(C);    

        	result R( W1.exec( sql ));
      		
      		W1.commit();
		int userFlag = 0, passFlag =0;
        	for (result::const_iterator c = R.begin(); c != R.end(); ++c)
		{			
			const char* resultStr = c[0].as<std::string>().c_str();
			std::string resultPass = c[1].as<std::string>();
			//const char* resultPass = c[1].as<std::string>().c_str();
			
	   		if (strcmp(inpU,resultStr)==0)
			{
				userFlag=1;
				
				std::string hashedPassword = generatehash(inpPassword);
				//std::cout<<"Password entered by user  "<<hashedStr<<std::endl;
				//std::cout<<"Password obtained by data "<<resultPass<<std::endl;
				//const char* hashedPass = hashedPassword.c_str();
			
				if (strcmp_me(hashedPassword,resultPass)==0)
				{
					passFlag=1;
				}
				break;
	   		}
        	}// for loop ends
		if(userFlag ==0)
		{	std::cout<<"Username not found"<<std::endl;
			C.disconnect();
			return "";
		}
		else if(userFlag ==1 && passFlag ==0)
		{
			std::cout<<"Invalid Password"<<std::endl;
			C.disconnect();
			return "";
		}
		else if(userFlag ==1 && passFlag ==1)
		{
			time_t curr_sec;
			time_t expiration_time;

			//if token already exists and request for auth comes again then generate token again and replace it.
			work W2(C);
			sql2 = (char*)"SELECT username from tokenTable";
        		result R( W2.exec( sql2 ));
      			W2.commit();
			for (result::const_iterator c = R.begin(); c != R.end(); ++c)
			{
				const char* nameFromResult = c[0].as<std::string>().c_str();
				if (strcmp(inpU,nameFromResult)==0)
				{
					alreadyExistsFlag =1;
					curr_sec = time (NULL);
					expiration_time =  curr_sec +1200;
					token = hashtoken(inpUsername,curr_sec);
					work W3(C);
					std::stringstream s1;
					s1<< "UPDATE tokenTable set token = '"<< token <<"', expiration ='"<< expiration_time <<"' where USERNAME='" <<inpUsername <<"'";
					W3.exec(s1.str());
					W3.commit();

				}//if ends
			}//for loop ends
			
			if (alreadyExistsFlag == 0)
			{
				curr_sec = time (NULL);
				expiration_time =  curr_sec +1200; //expiration time is set 20mins i.e 1200secs later than current epoch time
			
				token = hashtoken(inpUsername,curr_sec);

				work W4(C);
				std::stringstream ss;
				ss << "INSERT INTO tokenTable (username,token,expiration) VALUES ('" << inpUsername << "','" << token << "','" <<expiration_time << "');";
				W4.exec(ss.str());
				W4.commit();
			}//if stat for alreadyExistsFlag ends
			
		}
		C.disconnect();
		return token;
	}
	catch (const std::exception &e){
      	std::cerr << e.what() << std::endl;
   	}

}
