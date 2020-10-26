-- USE leetcode;
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