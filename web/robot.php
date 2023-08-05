<?php
$url = $_SERVER['REQUEST_SCHEME'].'://'.$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
if(isset($_POST['action'])) {
  $action = preg_match('/^[fsb][fsb]$/', $_POST['action']) ? $_POST['action'] : 'ss';
  file_put_contents("motion.txt", $action);
  header('Location: '.$url);
}  
?><!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
  form {
    display: grid;
    width: 90vw;
    margin: 0 auto;
    grid-template: 100px 100px 100px 100px 100px/ 1fr 1fr 1fr;
  }
  button {
    font-size: 5rem;
    display: block;
  }
  button:nth-of-type(1) {
   grid-column: 2/3; 
  }
  button:nth-of-type(2) {
   grid-row: 2/3; 
   grid-column: 1/2; 
  }
  button:nth-of-type(3) {
   grid-row: 2/3; 
   grid-column: 2/3; 
  }
  button:nth-of-type(4) {
   grid-row: 2/3; 
   grid-column: 3/4; 
  }
  button:nth-of-type(5) {
   grid-row: 3/4; 
   grid-column: 2/3; 
  }
  button:nth-of-type(6) {
   grid-row: 5/6; 
   grid-column: 1/2; 
  }
  button:nth-of-type(7) {
   grid-row: 5/6; 
   grid-column: 2/3; 
  }
  button:nth-of-type(8) {
   grid-row: 5/6; 
   grid-column: 3/4; 
   transform: rotate(180deg);
  }
</style>
</head>
<body>
  <form method="post">
   <button name="action" value="ff" type="submit">&uarr;</button>
   <button name="action" value="fs" type="submit">&larr;</button>
   <button name="action" value="ss" type="submit">&#9632;</button>
   <button name="action" value="sf" type="submit">&rarr;</button>
   <button name="action" value="bb" type="submit">&darr;</button>
   <button name="action" value="bf" type="submit">&#9100;</button>
   <button name="action" value="ss" type="submit">&#9632;</button>
   <button name="action" value="fb" type="submit">&#9100;</button>
  </form>
</body>
</html>
