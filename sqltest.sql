
SELECT * from sqlite_master;


-- 175. Combine Two Tables
Drop TABLE Person;
Create table If Not Exists Person (PersonId int, FirstName varchar(255), LastName varchar(255));
Truncate table Person;
DELETE from person;
insert into Person (PersonId, LastName, FirstName) values ('1', 'Wang', 'Allen');
insert into Person (PersonId, LastName, FirstName) values ('2', 'chen', 'cay');
Truncate table Address;

DELETE from Address;
Create table If Not Exists Address (AddressId int, PersonId int, City varchar(255), State varchar(255));
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York');
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York');

select * from  person;
select * from address;
--  304 ms,82.12%
select DISTINCT person.FirstName,person.LastName,Address.City,Address.State FROM
person LEFT JOIN Address on Person.PersonId == address.AddressId;



-- 176. Second Highest Salary

Create table If Not Exists Employee (Id int, Salary int);
Truncate table Employee
-- DELETE from Employee;
insert into Employee (Id, Salary) values ('1', '100');
insert into Employee (Id, Salary) values ('2', '200');
insert into Employee (Id, Salary) values ('3', '300');

SELECT * FROM Employee;

-- select * from Employee ORDER BY Salary DESC LIMIT 1,1;
-- select * from Employee ORDER BY Salary DESC LIMIT 1 OFFSET  1;

--  158 ms, faster than 99.37%
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
Truncate table Person;
insert into Person (Id, Email) values ('1', 'a@b.com');
insert into Person (Id, Email) values ('2', 'c@d.com');
insert into Person (Id, Email) values ('3', 'a@b.com');
SELECT * from Person;
-- 436 ms, faster than 14.94%
SELECT email from Person group by email HAVING count(*)>1;
-- 323 ms, faster than 67.12% 
SELECT DISTINCT a.email FROM Person a, Person b WHERE a.id != b.id AND a.email = b.email;
-- 309 ms, faster than 77.29%
select Email from
(
  select Email, count(Email) as num
  from Person
  group by Email
) as statistic
where num > 1;

-- 183. Customers Who Never Order
DROP TABLE Customers;
Create table If Not Exists Customers (Id int, Name varchar(255));
Truncate table Customers;
insert into Customers (Id, Name) values ('1', 'Joe');
insert into Customers (Id, Name) values ('2', 'Henry');
insert into Customers (Id, Name) values ('3', 'Sam');
insert into Customers (Id, Name) values ('4', 'Max');

SELECT * FROM Customers;

Create table If Not Exists Orders (Id int, CustomerId int);
Truncate table Orders;
insert into Orders (Id, CustomerId) values ('1', '3');
insert into Orders (Id, CustomerId) values ('2', '1');

SELECT * FROM Orders;

-- 426 ms, faster than 84.11%
SELECT Name FROM Customers  LEFT JOIN Orders  ON Customers.Id = Orders.CustomerId 
WHERE CustomerId IS NULL;

--  515 ms, faster than 36.64%
SELECT Name AS Customers FROM Customers WHERE id not in (SELECT customerid FROM Orders);



-- 196. Delete Duplicate Emails
Create table If Not Exists Person (Id int, Email varchar(255));
Truncate table Person;
insert into Person (Id, Email) values ('1', 'a@b.com');
insert into Person (Id, Email) values ('2', 'c@d.com');
insert into Person (Id, Email) values ('3', 'a@b.com');
SELECT * from Person;
-- INSERT INTO Person VALUES(3,'a@b.com');
-- 1762 ms,51.1%
delete p1 from Person p1, Person p2 where p1.Email = p2.Email and p1.id > p2.id;
-- DELETE FROM Person WHERE Id in (SELECT p1.Id from  Person p1, Person p2 WHERE p1.Email == p2.Email AND p1.Id > p2.Id);




-- 197. Rising Temperature
Create table If Not Exists Weather (Id int, RecordDate date, Temperature int) ;
Truncate table Weather ;
insert into Weather (Id, RecordDate, Temperature) values ('1', '2015-01-01', '10') ;
insert into Weather (Id, RecordDate, Temperature) values ('2', '2015-01-02', '25') ;
insert into Weather (Id, RecordDate, Temperature) values ('3', '2015-01-03', '20') ;
insert into Weather (Id, RecordDate, Temperature) values ('4', '2015-01-04', '30') ;

SELECT * FROM Weather;

-- 307 ms, faster than 94.47%
SELECT a.id FROM Weather a, Weather b WHERE a.RecordDate=DATE_ADD(b.RecordDate, INTERVAL 1 day) and a.Temperature > b.Temperature;

-- 408 ms, faster than 75.94%
SELECT a.id FROM Weather a, Weather b WHERE DATEDIFF(a.RecordDate,b.RecordDate)=1 and a.Temperature > b.Temperature;



-- SELECT DATE(RecordDate),DATE(RecordDate,'-1 day') FROM Weather;
-- SELECT w1.Id from Weather w1, Weather w2 WHERE w1.Temperature > w2.Temperature 
-- AND DATE(w1.RecordDate,'-1 day') == DATE(w2.RecordDate);


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
SELECT name,population,area FROM World WHERE area > 3000000 OR population > 25000000;



-- 596. Classes More Than 5 Students
Create table If Not Exists courses (student varchar(255), class varchar(255)) ;
Truncate table courses ;
insert into courses (student, class) values ('A', 'Math') ;
insert into courses (student, class) values ('B', 'English') ;
insert into courses (student, class) values ('C', 'Math') ;
insert into courses (student, class) values ('D', 'Biology') ;
insert into courses (student, class) values ('E', 'Math') ;
insert into courses (student, class) values ('F', 'Computer') ;
insert into courses (student, class) values ('G', 'Math') ;
insert into courses (student, class) values ('H', 'Math') ;
insert into courses (student, class) values ('I', 'Math') ;

SELECT * FROM courses;

-- DELETE FROM courses WHERE ROWID not in (SELECT ROWID FROM courses  GROUP BY student,class HAVING count(*)>1);
-- 540 ms, toooo slow
SELECT  student FROM courses GROUP BY class HAVING count( student)>1 ;

-- 282 ms, faster than 56.95%
SELECT class 
FROM
    (SELECT class, COUNT(DISTINCT student) AS num FROM courses
    GROUP BY class) AS temp_table
WHERE
    num >= 5;



-- 620. Not Boring Movies
Create table If Not Exists cinema (id int, movie varchar(255), description varchar(255), rating float(2, 1));
Truncate table cinema;
insert into cinema (id, movie, description, rating) values ('1', 'War', 'great 3D', '8.9');
insert into cinema (id, movie, description, rating) values ('2', 'Science', 'fiction', '8.5');
insert into cinema (id, movie, description, rating) values ('3', 'irish', 'boring', '6.2');
insert into cinema (id, movie, description, rating) values ('4', 'Ice song', 'Fantacy', '8.6');
insert into cinema (id, movie, description, rating) values ('5', 'House card', 'Interesting', '9.1');

SELECT * FROM cinema;
-- 240 ms, faster than 22.96% o
SELECT * FROM cinema WHERE id % 2 != 0 AND description != 'boring' ORDER BY rating DESC;
-- 172 ms, faster than 91.30% 
SELECT * FROM cinema WHERE MOD(id,2)=1 AND description <> 'boring' ORDER BY rating DESC;


-- 627. Swap Salary
create table if not exists salary(id int, name varchar(100), sex char(1), salary int);
Truncate table salary;
insert into salary (id, name, sex, salary) values ('1', 'A', 'm', '2500');
insert into salary (id, name, sex, salary) values ('2', 'B', 'f', '1500');
insert into salary (id, name, sex, salary) values ('3', 'C', 'm', '5500');
insert into salary (id, name, sex, salary) values ('4', 'D', 'f', '500');
SELECT * FROM Salary;

-- 241 ms, faster than 44.80% 
UPDATE salary SET sex = char(Ascii(sex) ^ Ascii('m') ^ Ascii('f'));

-- 188 ms, faster than 96.13% 
UPDATE salary
SET sex = 
        CASE sex  WHEN 'f' THEN 'm' ELSE 'f' 
        END;

