alter table employee 
    drop FOREIGN KEY fk_super_ssn;

alter table employee 
    drop FOREIGN KEY fk_dno;

alter table department 
    drop FOREIGN KEY fk_mgr_ssn;

alter table dept_locations 
    drop FOREIGN KEY fk_dlocation;

alter table works_on 
    drop FOREIGN KEY fk_works_on_pno;

alter table works_on 
    drop FOREIGN KEY fk_works_on_ssn;

alter table project 
    drop FOREIGN KEY fk_project;

alter table dependent
    drop FOREIGN KEY fk_dependent;

drop table department;
drop table dependent;
drop table employee;
drop table project;
drop table works_on;
drop table dept_locations;

drop database imt2019092_companydb;
