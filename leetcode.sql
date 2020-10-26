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


-- 626	Exchange Seats   

-- 178	Rank Scores    

-- 185. Department Top Three Salaries

-- 601. Human Traffic of Stadium

-- 262. Trips and Users