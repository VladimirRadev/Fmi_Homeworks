<?php
function getUser($id) {
    //validating id
    if (!(is_numeric($id) && $id >= 0))
    {
        return null;
    }

    $userId = $id; 

    $db= new Db();
    $connection=$db->getConnection();
    $sql = "SELECT * from users where id = :userId";


    $stmt = $connection->prepare($sql);
    $stmt->execute(["userId" => $userId]);

    $user = $stmt->fetch(PDO::FETCH_ASSOC);


    if(!empty($user)) {
        return $user;
    }
    else {
        return null;
    }
}
?>