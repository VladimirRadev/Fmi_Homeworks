<?php 


$data = json_decode(file_get_contents('php://input'),true);
$message = array("message"=>'User with email: ' . $data['email'] . ' , first_name: ' . $data['first_name'] . 
' has been signed to ' . $data['type']); 
echo json_encode($message);


?>