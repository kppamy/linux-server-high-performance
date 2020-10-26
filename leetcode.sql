-- USE leetcode;

-- 1179. Reformat Department Table
Create table If Not Exists Department (id int, revenue int, month varchar(5));
Truncate table Department;
insert into Department (id, revenue, month) values ('1', '8000', 'Jan');
SELECT * FROM Department;
insert into Department (id, revenue, month) values ('1', '7000', 'Feb');
insert into Department (id, revenue, month) values ('1', '6000', 'Mar');
insert into Department (id, revenue, month) values ('3', '10000', 'Feb');
insert into Department (id, revenue, month) values ('2', '9000', 'Jan');

SELECT 
    id,
    sum(if( month = 'Jan', revenue, null )) as Jan_Revenue,
    sum(if( month = 'Feb', revenue, null )) AS Feb_Revenue,
    sum(if( month = 'Mar', revenue, null )) AS Mar_Revenue,
    sum(if( month = 'Apr', revenue, null )) AS Apr_Revenue,
    sum(if( month = 'May', revenue, null )) AS May_Revenue,
    sum(if( month = 'Jun', revenue, null )) AS Jun_Revenue,
    sum(if( month = 'Jul', revenue, null )) AS Jul_Revenue,
    sum(if( month = 'Aug', revenue, null )) AS Aug_Revenue,
    sum(if( month = 'Sep', revenue, null )) AS Sep_Revenue,
    sum(if( month = 'Oct', revenue, null )) AS Oct_Revenue,
    sum(if( month = 'Nov', revenue, null )) AS Nov_Revenue,
    sum(if( month = 'Dec', revenue, null )) AS Dec_Revenue
FROM
    Department 
GROUP BY
    id;

-- 180. Consecutive Numbers
Create table If Not Exists Logs (Id int, Num int) ;
Truncate table Logs ;
insert into Logs (Id, Num) values ('1', '1') ;
insert into Logs (Id, Num) values ('2', '1') ;
insert into Logs (Id, Num) values ('3', '1') ;
insert into Logs (Id, Num) values ('4', '2') ;
insert into Logs (Id, Num) values ('5', '1') ;
insert into Logs (Id, Num) values ('6', '2') ;
insert into Logs (Id, Num) values ('7', '2') ;

SELECT * FROM Logs;

-- SELECT DISTINCT l1.Id FROM LOGS l1, LOGS l2, LOGS l3
-- WHERE l2.id=l1.id+1 and l3.id=l2.id+1 and l1.num=l2.num and l2.num=l3.num;

SELECT 
    DISTINCT Num AS ConsecutiveNums 
FROM Logs 
where (Id+1,num) in (SELECT * FROM LOGS) and (Id +2,num) in (SELECT * FROM Logs);



-- 184	Department Highest Salary    
DROP TABLE Department;
SELECT * FROM information_schema.tables WHERE TABLE_SCHEMA='leetcode';
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, DepartmentId int) ;
Truncate table Employee ;
insert into Employee (Id, Name, Salary, DepartmentId) values ('1', 'Joe', '70000', '1') ;
insert into Employee (Id, Name, Salary, DepartmentId) values ('2', 'Jim', '90000', '1') ;
insert into Employee (Id, Name, Salary, DepartmentId) values ('3', 'Henry', '80000', '2') ;
insert into Employee (Id, Name, Salary, DepartmentId) values ('4', 'Sam', '60000', '2') ;
insert into Employee (Id, Name, Salary, DepartmentId) values ('5', 'Max', '90000', '1') ;
SELECT * FROM Employee;


Create table If Not Exists Department (Id int, Name varchar(255)) ;
Truncate table Department ;
insert into Department (Id, Name) values ('1', 'IT') ;
insert into Department (Id, Name) values ('2', 'Sales') ;
SELECT * FROM Department;


SELECT 
    DISTINCTROW  department.NAME as Department, Employee, Salary  
FROM 
    (SELECT 
        Employee.Salary,Employee.Departmentid,Employee.Name AS Employee 
    FROM 
        (SELECT DepartmentId, max(Salary) as Salary FROM Employee GROUP BY DepartmentId) as maxinfo, Employee 
    WHERE Employee.DepartmentId= maxinfo.DepartmentId and Employee.Salary=maxinfo.Salary) 
    as temp 
    Inner join Department on (temp.Departmentid=Department.id)
ORDER BY Department; 


  
SELECT
    department.NAME AS Department,Employee.Name AS Employee, Employee.Salary
FROM 
    (SELECT DepartmentId, max(Salary) as Salary FROM Employee GROUP BY DepartmentId) as maxinfo, Employee,department 
WHERE
    Employee.DepartmentId= maxinfo.DepartmentId 
    and Employee.Salary=maxinfo.Salary 
    and Employee.DepartmentId=department.id;


select department, employee, salary
from
(
select a.name as employee,b.name as department, salary, dense_rank() 
    over(partition by b.name order by a.salary desc) as rn
from employee a
inner join department b on a.departmentid = b.id
) t1
where rn = 1;

-- 626	Exchange Seats   
Create table If Not Exists seat(id int, student varchar(255)) ;
Truncate table seat ;
insert into seat (id, student) values ('1', 'Abbot') ;
insert into seat (id, student) values ('2', 'Doris') ;
insert into seat (id, student) values ('3', 'Emerson') ;
insert into seat (id, student) values ('4', 'Green') ;
insert into seat (id, student) values ('5', 'Jeames') ;
SELECT * From seat;

SELECT a.id,b.student
FROM seat a, seat b
WHERE (b.id=a.id+1 AND a.id%2=1) OR (b.id=a.id-1 AND a.id%2=0) 
    OR (a.id%2=1 AND a.id+1 NOT IN (select id FROM seat) AND a.id=b.id)
ORDER BY Id;


-- 178	Rank Scores    

-- 185. Department Top Three Salaries

-- 601. Human Traffic of Stadium

-- 262. Trips and Users