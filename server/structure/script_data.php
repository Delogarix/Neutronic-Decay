<?php

$db_passwd = "SH9z2V";
$timeToFinish = 70;

try {

    $db_server = new PDO(
        'mysql:host=localhost;dbname=gamedb;charset=utf8',
        'root',
        $db_passwd
    );

    $dbQuery = 'SELECT * FROM JOUEUR';
    $dbQueryBoard = 'SELECT username_score, temps, hasWin FROM SCORE ORDER BY temps DESC';
    $db_data = $db_server->prepare($dbQuery);
    $db_data->execute();
    $cred2 = $db_data->fetchAll();

    $db_data = $db_server->prepare($dbQueryBoard);
    $db_data->execute();
    $scoreboard = $db_data->fetchAll();

}

catch (Exception $e) {
    die('Erreur : ' . $e->getMessage());
}


function isValueAtKey($value, $key, array $array) : bool { // Pour les tableau associatif
    foreach($array as $elem) {
        if (key_exists($key, $elem)) {
            if ($value === $elem[$key]) return true;
        }
    }
    return false;
}

function isLoginValid($login, $password, $datas) : bool {

    foreach ($datas as $data) {
        if ($data["username"] === $login && $data["password"] === $password) {
            return true;
        }
    }
    return false;
}

function isLoginExist($login, $datas) : bool {
    if (!isset($login)) return false;
    foreach ($datas as $data) {
        if ($data["username"] === $login) {
            return true;
        }
    }
    return false;
}

?>