

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





