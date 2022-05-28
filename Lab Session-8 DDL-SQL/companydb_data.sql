insert into employee(fname, minit, lname, ssn, bdate, address, sex, salary, super_ssn, dno)
	values
		('John', 'B', 'Smith', '123456789', '1965-01-09', '731,Fondren, Houston, TX', 'M', 30000, NULL, NULL),
		('Franklin', 'T', 'Wong', '333445555', '1955-12-08', '638,Voss, Houston, TX', 'M', 40000, NULL, NULL),
		('Alicia', 'J', 'Zelaya', '999887777', '1968-01-19', '3321,Castle, Spring, TX', 'F', 25000, NULL, NULL),
		('Jennifer', 'S', 'Wallace', '987654321', '1941-06-20', '291,Berry , Blaire, TX', 'F', 43000, NULL, NULL),
		('Ramesh', 'K', 'Narayan', '666884444', '1962-09-15', '975,FireOak, Humble, TX', 'M', 38000, NULL, NULL),
		('Joyce', 'A', 'English', '453453453', '1972-07-31', '5631,Rice, Houston, TX', 'F', 25000, NULL, NULL),
		('Ahmed', 'V', 'Jabbar', '987987987', '1969-03-29', '980,Dallas, Houston, TX', 'M', 25000, NULL, NULL),
		('James', 'E', 'Borg', '888665555', '1937-11-10', '450 Stone, Houston, TX', 'M', 55000, NULL, NULL);

insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
	values
		('Research', 5, '333445555', '1988-05-22'),
		('Administration', 4, '987654321', '1995-01-01'),
		('Headquarters', 1, '888665555', '1981-06-19');

insert into dept_locations(dnumber, dlocation)
	values
		(1, 'Houston'),
		(4, 'Stafford'),
		(5, 'Bellare'),
		(5, 'Sugarland'),
		(5, 'Houston');

insert into project(pname, pnumber, plocation, dnum)
	values
		('ProductX', 1, 'Bellaire', 5),
		('ProductY', 2, 'Sugarland', 5),
		('ProductZ', 3, 'Houston', 5),
		('Computerization', 10, 'Stafford', 4),
		('Reorganisation', 20, 'Houston', 1),
		('Newbenefits', 30, 'Stafford', 4);

insert into works_on(essn,pno,hours)
	values
		('123456789', 1, 32.5),
		('123456789', 2, 7.5),
		('666884444', 3, 40.0),
		('453453453', 1, 20.0),
		('453453453', 2, 20.0),
		('333445555', 2, 10.0),
		('333445555', 3, 10.0),
		('333445555', 10, 10.0),
		('333445555', 20, 10.0),
		('999887777', 30, 30.0),
		('999887777', 10, 10.0),
		('987987987', 10, 35.0),
		('987987987', 30, 5.0),
		('987654321', 30, 20.0),
		('987654321', 20, 15.0),
		('888665555', 20, NULL);

insert into dependent(essn, dependent_name, sex, bdate, relationship)
	values
		('333445555', 'Alice', 'F', '1986-04-05', 'Daughter'),
		('333445555', 'Theodore', 'M', '1983-10-25', 'Son'),
		('333445555', 'Joy', 'F', '1958-05-03', 'Spouse'),
		('987654321', 'Abner', 'M', '1942-02-28', 'Spouse'),
		('123456789', 'Michael', 'M', '1988-01-04', 'Son'),
		('123456789', 'Alice', 'F', '1988-12-30', 'Daughter'),
		('123456789', 'Elizabeth', 'F', '1967-05-05', 'Spouse');

update employee
	set super_ssn = '333445555', dno=5
	where ssn='123456789';

update employee
	set super_ssn = '888665555', dno=5
	where ssn='333445555';

update employee
	set super_ssn = '987654321', dno=4
	where ssn='999887777';

update employee
	set super_ssn = '888665555', dno=4
	where ssn='987654321';

update employee
	set super_ssn = '333445555', dno=5
	where ssn='666884444';

update employee
	set super_ssn = '333445555', dno=5
	where ssn='453453453';

update employee
	set super_ssn = '987654321', dno=4
	where ssn='987987987';

update employee
	set dno=1
	where ssn='888665555';

select * from employee;
select * from department;
select * from project;
select * from dependent;
select * from dept_locations;
select * from works_on;
