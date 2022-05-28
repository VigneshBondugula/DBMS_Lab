create database imt2019092_companydb;
use imt2019092_companydb;

create table department(
    dname varchar(30) NOT NULL,
    dnumber smallint,
    mgr_ssn char(9),
    mgr_start_date date,
    constraint pk_department PRIMARY KEY (dnumber)
);

create table employee(
    fname varchar(30) NOT NULL,
    minit char(1),
    lname varchar(30),
    ssn char(9),
    bdate date,
    address varchar(50),
    sex char(1),
    salary bigint,
    super_ssn char(9),
    dno smallint,
    constraint pk_employee PRIMARY KEY (ssn)
);

create table dept_locations(
    dnumber smallint,
    dlocation varchar(20),
    constraint pk_dept_loc PRIMARY KEY (dnumber, dlocation)
);

create table works_on(
    essn char(9),
    pno smallint,
    hours float(3,1),
    constraint pk_works_on PRIMARY KEY (essn, pno)
);

create table project(
    pname varchar(30),
    pnumber smallint,
    plocation varchar(20),
    dnum smallint,
    constraint pk_project PRIMARY KEY (pnumber)
);

create table dependent(
    essn char(9),
    dependent_name varchar(30),
    sex char(1),
    bdate date,
    relationship varchar(20),
    constraint pk_dependent PRIMARY KEY (essn, dependent_name)
);

