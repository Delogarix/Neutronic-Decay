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
    $dbQueryBoard = 'SELECT username_score, temps, hasWin FROM SCORE
                    GROUP BY username_score
                    ORDER BY temps DESC';
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
"blackcurrent",
"stew",
"mushroom",
"cabbage",
"sauerkraut",
"lemon",
"coalfish",
"scallop"
];

/*
chop
sauce
prawn
toasted sandwich (cheese,ham)
raw vegetable
sea bream
lunch
turkey
sweet
mineral water
still/fizzy
shallot
rib steak
first course 
stuffed
sirloin
fennel
flaky pastry
liver pâté
goose/duck
strawberry
raspberry
french fries, chips
cold
cheese
king prawn
cake
game
leg of lamb
ice (cream)
dish browned in oven
redcurrant
shepherds pie
herring
bean
lobster
oil
oyster
snow egg with sauce
herb tea
ham
juice
white wine with cassis
milk
lettuce
crawfish
rabbit
bacon
vegetable
lentil
hare
lemonade
burbot
sea bass


fillet of duck
maize, sweetcorn
chestnut
preserved chestnut
mint
menu
cooked in browned butter
honey
morel
mustard
bilberry


lamb stew
turnip
pasta


soft boiled egg
hard boiled egg
fried egg
scambled eggs
goose
onion
omelet
steak


bread
grapefruit
pasta
pastry
peach
partridge
parsley
breakfast
salt pork
green peas
pepper
guinea hen
daily special 
pear
leek
fish
pepper
apple
potato
chips
beef stew
chicken
stew
ray
grape
vegetable stew
greengage
rice
kidney
rosemary
roast
red mullet
fish soups
saffron
rare
salted
zandre
pork sausage
cooked dried sausage
salmon
salt
sole
bran
soupe
sugar
cup
paté
head
tea
tuna fish
lukewarm
lime tea
herbal tea
slice
truffle
veal
cream soup
glass
vervain
meat
wine*/



?>