<?php


$data=file_get_contents('php://input');
$arr = json_decode($data,true);   
echo json_encode($arr);
?>