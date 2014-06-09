--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: tokentable; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE tokentable (
    username text NOT NULL,
    token text NOT NULL,
    expiration integer NOT NULL
);


ALTER TABLE public.tokentable OWNER TO postgres;

--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE users (
    username text NOT NULL,
    password text NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Data for Name: tokentable; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY tokentable (username, token, expiration) FROM stdin;
harkirat	fd97b92e4c7da9267d200eddfb22313bbd6b569ad5fb30936e31a1eedd541edb	1402303168
ayush	4f0d4aa9878944ece815f78354d75c5515f677cd9b8fd9c5c7fda6cee2e28eb7	1402303178
garvita	77558f851ebbbfd669e2458e50d054c7fcd4e3d4dbb34241626bcafd4a8e51c3	1402303184
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY users (username, password) FROM stdin;
harkirat	c18a646030627ac65906951044823ff8494e45aa79aa72c3bdbc5a61a739b1f6
ayush	bddbfd233f554386d852d13efe35c1d4a027d8ddab9cb916fe9e1f548f97e35d
garvita	0f68d3a0c87c7a83c0500708486387eb822e08d59566635ba254a633734b4478
\.


--
-- Name: tokentable_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY tokentable
    ADD CONSTRAINT tokentable_pkey PRIMARY KEY (username);


--
-- Name: users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY users
    ADD CONSTRAINT users_pkey PRIMARY KEY (username);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

