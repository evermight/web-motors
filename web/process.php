<?php
if(isset($_REQUEST['action'])) {
  $action = preg_match('/^[fsb][fsb]$/', $_REQUEST['action']) ? $_REQUEST['action'] : 'ss';
  file_put_contents("motion.txt", $action);
  die($action);
}