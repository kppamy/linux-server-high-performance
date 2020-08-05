

-- 175. Combine Two Tables
Drop TABLE Person;
Create table If Not Exists Person (PersonId int, FirstName varchar(255), LastName varchar(255));
-- Truncate table Person;
DELETE from person;
insert into Person (PersonId, LastName, FirstName) values ('1', 'Wang', 'Allen');
insert into Person (PersonId, LastName, FirstName) values ('2', 'chen', 'cay');
-- Truncate table Address;

DELETE from Address;
Create table If Not Exists Address (AddressId int, PersonId int, City varchar(255), State varchar(255));
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York');
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York');
select * from  person;
select * from address;
select DISTINCT person.FirstName,person.LastName,Address.City,Address.State FROM
person LEFT JOIN Address on Person.PersonId == address.AddressId;

-- 176. Second Highest Salary
DROP TABLE Employee;
Create table If Not Exists Employee (Id int, Salary int);
-- Truncate table Employee
DELETE from Employee;
insert into Employee (Id, Salary) values ('1', '100');
insert into Employee (Id, Salary) values ('2', '200');
insert into Employee (Id, Salary) values ('3', '300');
-- select * from Employee ORDER BY Salary DESC LIMIT 1,1;
-- select * from Employee ORDER BY Salary DESC LIMIT 1 OFFSET  1;
select ifnull((select DISTINCT salary from Employee 
Order by Salary DESC LIMIT 1,1),null) as  SecondHighestSalary;
