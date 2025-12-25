<header>
    <nav class="navbar justify-content-center">
        <ul class="list-group list-group-horizontal row">
            <li class="list-group-item col "><a class="link-info" href="index.php">Index</a></li>

            <?php if (isset($_SESSION['logged']) && $_SESSION['logged']): ?>
                <li class="list-group-item col"> <a clas="link-primary" href="leaderboard.php">Leaderboard</a></li>
            <?php endif ?>

            <?php if(isset($_SESSION['logged']) && $_SESSION['logged'] ): ?>
                <li class="list-group-item col"><a class="link-primary" href="../build/game.html">Game</a></li>
            <?php endif ?>

            <?php if(isset($_SESSION['logged']) && $_SESSION['logged']): ?>
                <li class="list-group-item col"><a class="link-info" href="disconnect.php">Disconnect</a></li>
            <?php else: ?>
                <li class="list-group-item col"><a class="link-info" href="login.php">Login</a></li>
            <?php endif ?>
        </ul>
    </nav>
</header>