<html>

<head>
</head>


<body>
<?php

$first = (isset($_GET['firstname']) ? $_GET['firstname'] : null);
$last = (isset($_GET['lastname']) ? $_GET['lastname'] : null);
$email = (isset($_GET['email'])? $_GET['email'] : null);





$dbc = mysqli_connect
('localhost', 'root', 'toucan', 'php_portfolio')
OR die
(mysqli_connect_error());

//selects database
mysqli_select_db($dbc,'php_portfolio');

//inserts new data
$q = "INSERT INTO people(firstname, lastname, email) 
VALUES ('$first', '$last', '$email')";
 mysqli_query($dbc, $q);


//selects the database
$q = 'SELECT * FROM people';
$r = mysqli_query($dbc, $q)
OR die
(mysqli_error());

echo 'people';

//formats database information on the page
while($row = mysqli_fetch_array ($r, MYSQL_ASSOC))
{
echo '<br />' .$row['firstname']. '|'. $row['lastname']. '|'. $row['email'];

}

//close mysql
  mysqli_close($dbc)
?>


</body>

</html>