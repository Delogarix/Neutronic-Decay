<?php

$db_passwd = "TTJDSk";
$timeToFinish = 70;

try {

    $db_server = new PDO(
        'mysql:host=localhost;dbname=gamedb;charset=utf8',
        'root',
        $db_passwd
    );

    /**
     * Meiller score par personne : 'SELECT username_score, max(temps) FROM SCORE GROUP BY username_score'
     * Meilleur avec tris par temps : 'SELECT username_score, max(temps) FROM SCORE GROUP BY username_score ORDER BY max(temps) DESC'
     */

    $dbQuery = 'SELECT * FROM JOUEUR';
    $dbQueryBoard = 'SELECT username_score, max(temps) as temps, hasWin FROM SCORE GROUP BY username_score ORDER BY max(temps) DESC';
    $db_data = $db_server->prepare($dbQuery);
    $db_data->execute();
    $cred2 = $db_data->fetchAll();

    $db_data = $db_server->prepare($dbQueryBoard);
    $db_data->execute();
    $scoreboard = $db_data->fetchAll();

}

catch (Exception $e) {
    //die('Erreur : ' . $e->getMessage());
    echo "Impossible de se connecter à la base de donnée : " . $e->getMessage(); 
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

$pass_set = [
"lamb",
"garlic",
"cranberry",
"almond",
"pineapple",
"anchovy",
"sausage", 
"artichoke",
"asparagus",
"avocado",
"sea-bass",
"saddle",
"basil",
"fritter",
"beetroot",
"butter",
"beer",
"beef",
"drink",
"sausage",
"bottle",
"coffee",
"cinnamon",
"ribs",
"menu",
"stew",
"mushroom",
"cabbage",
"sauerkraut",
"lemon",
"coalfish",
"scallop",
"chop",
"sauce",
"prawn",
"lunch",
"turkey",
"sweet",
"water",
"shallot",
"stuffed",
"sirloin",
"fennel",
"fries",
"cold",
"cheese",
"cake",
"ice",
"herring",
"bean",
"lobster",
"oil",
"oyster",
"ham",
"juice",
"milk",
"lettuce",
"crawfish",
"rabbit",
"bacon",
"vegetable",
"lentil",
"hare",
"lemonade",
"burbot",
"sweetcorn",
"chestnut",
"mint",
"menu",
"honey",
"morel",
"mustard",
"bilberry",
"turnip",
"pasta",
"goose",
"onion",
"omelet",
"steak",
"bread",
"pasta",
"pastry",
"peach",
"partridge",
"parsley",
"breakfast",
"pepper",
"pear",
"leek",
"fish",
"pepper",
"apple",
"potato",
"chips",
"chicken",
"stew",
"ray",
"grape",
"greengage",
"rice",
"kidney",
"rosemary",
"roast",
"saffron",
"rare",
"salted",
"zandre",
"salmon",
"salt",
"sole",
"bran",
"soupe",
"sugar",
"cup",
"paté",
"head",
"tea",
"lukewarm",
"slice",
"truffle",
"veal",
"glass",
"vervain",
"meat",
"wine"
];

?>