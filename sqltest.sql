
SELECT * from sqlite_master;


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

-- 181. Employees Earning More Than Their Managers
DROP TABLE Employee;
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, ManagerId int);
-- Truncate table Employee
insert into Employee (Id, Name, Salary, ManagerId) values ('1', 'Joe', '70000', '3');
insert into Employee (Id, Name, Salary, ManagerId) values ('2', 'Henry', '80000', '4');
insert into Employee (Id, Name, Salary, ManagerId) values ('3', 'Sam', '60000', 'None');
insert into Employee (Id, Name, Salary, ManagerId) values ('4', 'Max', '90000', 'None');
select * from Employee;
select e1.name from Employee e1, Employee e2 
where e1.Salary > e2.Salary and e1.ManagerId = e2.Id;


-- 182. Duplicate Emails
DROP TABLE Person;
Create table If Not Exists Person (Id int, Email varchar(255));
-- Truncate table Person;
insert into Person (Id, Email) values ('1', 'a@b.com');
insert into Person (Id, Email) values ('2', 'c@d.com');
insert into Person (Id, Email) values ('3', 'a@b.com');
SELECT * from Person;
SELECT email from Person group by email HAVING count(*)>1;



-- 183. Customers Who Never Order
DROP TABLE Customers;
Create table If Not Exists Customers (Id int, Name varchar(255));
DROP TABLE Orders;
Create table If Not Exists Orders (Id int, CustomerId int);
-- Truncate table Customers;
insert into Customers (Id, Name) values ('1', 'Joe');
insert into Customers (Id, Name) values ('2', 'Henry');
insert into Customers (Id, Name) values ('3', 'Sam');
insert into Customers (Id, Name) values ('4', 'Max');
-- Truncate table Orders;
insert into Orders (Id, CustomerId) values ('1', '3');
insert into Orders (Id, CustomerId) values ('2', '1');
SELECT * FROM Customers;
SELECT * FROM Orders;
SELECT Name FROM Customers  LEFT JOIN Orders  ON Customers.Id = Orders.CustomerId 
WHERE CustomerId IS NULL;

-- 196. Delete Duplicate Emails
SELECT * from Person;
-- INSERT INTO Person VALUES(3,'a@b.com');
-- delete p1 from Person p1, Person p2 where p1.Email = p2.Email and p1.id > p2.id;
DELETE FROM Person WHERE Id in (SELECT p1.Id from  Person p1, Person p2 WHERE p1.Email == p2.Email AND p1.Id > p2.Id);
-- DELETE from Person where id = (
    -- select MAX(ID) from Person group BY Email HAVING COUNT(*)>1);




-- 197. Rising Temperature
-- DELETE FROM Weather WHERE ROWID not in (SELECT DISTINCT (id) from Weather);
SELECT * FROM Weather;
SELECT DATE(RecordDate),DATE(RecordDate,'-1 day') FROM Weather;
SELECT w1.Id from Weather w1, Weather w2 WHERE w1.Temperature > w2.Temperature 
AND DATE(w1.RecordDate,'-1 day') == DATE(w2.RecordDate);


-- -- 595. Big Countries
-- -- DROP TABLE World;
Create table If Not Exists World (name varchar(255), continent varchar(255), area int, population int, gdp int);
-- -- Truncate table World;
insert into World (name, continent, area, population, gdp) values ('Afghanistan', 'Asia', '652230', '25500100', '20343000000');
insert into World (name, continent, area, population, gdp) values ('Albania', 'Europe', '28748', '2831741', '12960000000');
insert into World (name, continent, area, population, gdp) values ('Algeria', 'Africa', '2381741', '37100000', '188681000000');
insert into World (name, continent, area, population, gdp) values ('Andorra', 'Europe', '468', '78115', '3712000000');
insert into World (name, continent, area, population, gdp) values ('Angola', 'Africa', '1246700', '20609294', '100990000000');
SELECT  * FROM World;
DELETE FROM World WHERE ROWID IN (SELECT ROWID FROM World GROUP BY name HAVING count(*)>1);
SELECT name,population,area FROM World WHERE area > 3000000 AND population > 25000000;
