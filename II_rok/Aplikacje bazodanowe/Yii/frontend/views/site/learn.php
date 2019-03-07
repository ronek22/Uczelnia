<style>

    .btt {
        font-weight: 700;
        margin-top: 3px;
        border: none;
        background: #00b3ee;
        color: #f2f2f2;
        padding: 5px 30px 5px 30px;
        margin-left: 30px;
        font-size: 14px;
        transition: all 500ms ease;
    }

    .btt:hover {
        background: #ffcc00;
        color: #1a1a1a;
    }

    .under {
        padding: 5px 0px 5px 0px;
        border: 0;
        outline: 0;
        background: transparent;
        border-bottom: 3px solid #ffcc00;
    }
    .col-centered{
        float: none;
        margin: 0 auto;
    }


    @import url('https://fonts.googleapis.com/css?family=Lato');
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 400;
        src: local('Roboto Regular'),
        local('Roboto-Regular'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/2UX7WLTfW3W8TclTUvlFyQ.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 700;
        src: local('Roboto Bold'),
        local('Roboto-Bold'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/d-6IYplOFocCacKzxwXSOD8E0i7KZn-EPnyo3HZu7kw.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: italic;
        font-weight: 400;
        src: local('Roboto Italic'),
        local('Roboto-Italic'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/1pO9eUAp8pSF8VnRTP3xnvesZW2xOQ-xsNqO47m55DA.woff)
        format('woff');
    }


    .navbar-inverse{
        background-color: #1B1E2D;
    }

    h1 {
        font-family: 'Lato';
        font-size: 24px;
        font-style: normal;
        font-variant: normal;
        font-weight: bold;
        line-height: 66px;
    }
    h3 {
        font-family: 'Lato';
        font-size: 22px;
        font-style: normal;
        font-variant: normal;
        font-weight: 700;
        line-height: 15.4px;
    }

    h4 {
        font-family: 'Lato';
        font-size: 20px;
        font-style: normal;
        font-variant: normal;
        font-weight: 300;
        line-height: 15.4px;
    }

    body {
        font-family: 'Roboto', sans-serif;
        font-size: 13px;
    }

    p {
        font-family: 'Roboto', sans-serif;
        font-size: 13px;
    }

    hr {

        border: 0;
        height: 0;
        border-top: 1px solid rgba(0, 0, 0, 0.1);
        border-bottom: 1px solid rgba(255, 255, 255, 0.3);

    }


    *:focus {
        outline: 0;
    }

</style>
    <?php

    if (isset($_GET['save']) && $_GET['save'] == 1) {

        $model = new \backend\models\Wynik();
        $model->konto_id = Yii::$app->user->id;
        $model->zestaw_id = $_GET['set'];
        $model->data_wyniku = date('Y-m-d');
        $model->wynik = $_GET['score'];
        $model->insert();

        if (file_exists('answers.txt')) {
            unlink('answers.txt');
        }

        Yii::$app->response->redirect(['site/user']);
    }
    else if (isset($_GET['save']) && $_GET['save'] == 2) {
        if (file_exists('answers.txt')) {
            unlink('answers.txt');
        }
        Yii::$app->response->redirect(['site/index']);
    } else {
        function type($type, $array)
        {
            if ($type == 1) {
                echo '<div class="alert alert-success text-center" role="alert">Poprawna odpowiedź :)</div>';
            } else {
                $mess = $_GET['type'] == 1 ? $array[$_GET['step']]['en'] : $array[$_GET['step']]['pl'];
                echo '<div class="alert alert-danger text-center" role="alert">Zła odpowiedź:' .  $mess . '</div>';
            }
        }

        function isKeyExist($search, $file)
        {
            if (file_exists($file)) {
                $content = file_get_contents($file);

                $exp = explode('-', $content);
                foreach ($exp as $key => $value) {
                    $spl = explode(':', $value);
                    if (count($spl) == 2) {
                        if ($spl[0] == $search) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        $set = htmlspecialchars($_GET['set']);
        $data = (new \yii\db\Query())->select('id, nazwa, zestaw, ilosc_slowek, podkategoria_id')->from('zestaw')->where(['id' => $set])->one();
        $subcategory = (new \yii\db\Query())->select('nazwa')->from('podkategoria')->where(['id' => $data['podkategoria_id']])->one();

        $explode = preg_split("/\\r\\n|\\r|\\n/", $data['zestaw']);

        if($_GET['xd'] == 0 && $_GET['alg'] == 1) {
            $numbers = range(0,count($explode)-1); //utworzenie tablicy numerow od 0 do ilosci slowek
            shuffle($numbers); // pomieszanie numerow
            for ($h = 0; $h < count($explode); $h++) {
                $split = explode(';', $explode[$h]);
                if (count($split) == 2) {
                    $array[$numbers[$h]] = ['pl' => $split[0], 'en' => $split[1]]; //array[5] = 1, array[3] = 2
                }
            }

            $_GET['xd']++;
        }
        else if($_GET['xd'] == 0 && $_GET['alg'] == 2){
            $numbers = range(0,count($explode)-1); //utworzenie tablicy numerow od 0 do ilosci slowek
            shuffle($numbers); // pomieszanie numerow

            for ($h = 0; $h < count($explode); $h++) {
                $split = explode(';', $explode[$h]);
                if (count($split) == 2) {
                    $array[$numbers[$h]] = ['pl' => $split[0], 'en' => $split[1]]; //array[5] = 1, array[3] = 2
                }
            }
            $_GET['xd']++;

        }
        else if(isset($_GET['arrai'])){
            $numbers=$_GET['arrai'];
            for ($h = 0; $h < count($explode); $h++) {
                $split = explode(';', $explode[$h]);
                if (count($split) == 2) {
                    $array[$numbers[$h]] = ['pl' => $split[0], 'en' => $split[1]];
                }
            }
        }


        // Wysłano formularz
        if (isset($_GET['send']) && $_GET['send'] == 1) {
            if ($_GET['type'] == 1) {
                if (trim($_GET['answer']) == trim($array[$_GET['step']]['en'])) {
                    if (isKeyExist($_GET['step'], 'answers.txt') == false) {
                        file_put_contents('answers.txt', $_GET['step'] . ':' . $_GET['answer'] . '-', FILE_APPEND);
                    }
                    type(1,$array);
                } else {
                    if (isKeyExist($_GET['step'], 'answers.txt') == false) {
                        file_put_contents('answers.txt', $_GET['step'] . ':' . $_GET['answer'] . '-', FILE_APPEND);
                    }
                    type(2,$array);
                }

                $_GET['step']++;
            } else {
                if (trim($_GET['answer']) == trim($array[$_GET['step']]['pl'])) {
                    if (isKeyExist($_GET['step'], 'answers.txt') == false) {
                        file_put_contents('answers.txt', $_GET['step'] . ':' . $_GET['answer'] . '-', FILE_APPEND);
                    }
                    type(1,$array);
                } else {
                    if (isKeyExist($_GET['step'], 'answers.txt') == false) {
                        file_put_contents('answers.txt', $_GET['step'] . ':' . $_GET['answer'] . '-', FILE_APPEND);
                    }
                    type(2,$array);
                }

                $_GET['step']++;
            }

            /*function nextVal($array) {

                $next = rand(0, count($array) - 1);
                var_dump($next, isKeyExist($next, 'answers.txt'));
                if (isKeyExist($next, 'answers.txt')) {

                    if ((count($array) - 1) == $_GET['values']) {
                        return;
                    }

                    nextVal($array);

                } else {
                    $_GET['step'] = $next;
                    $_GET['values'] += 1;
                }
            }

            nextVal($shuffledArray);*/

        }
        $values = isset($_GET['values']) ? $_GET['values'] : 0;

        if ($_GET['step'] < count($array))
        {
            ?>
            <h4><?php echo $subcategory['nazwa']; ?>: <?php echo $data['nazwa']; ?></h4><hr>
            <div class="panel-body">
                <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="get">
                    <input type="hidden" name="r" value="site/learn">
                    <input type="hidden" name="type" value="<?php echo $_GET['type']; ?>">
                    <input type="hidden" name="set" value="<?php echo $set; ?>">
                    <input type="hidden" name="step" value="<?php echo $_GET['step']; ?>">
                    <input type="hidden" name="xd" value="<?php echo $_GET['xd']; ?>">
                    <?php
                    for ($h = 0; $h < count($explode); $h++) {
                        ?>
                        <input type="hidden" name="arrai[]" value="<?php echo $numbers[$h]; ?>">
                        <?php
                    }
                    ?>
                    <div class="row">
                        <div class="col-xs-12 col-sm-6 col-md-6 col-centered">

                            <h3><label for="word"><?php echo $_GET['type'] == 1 ? $array[$_GET['step']]['pl'] : $array[$_GET['step']]['en']; ?></label></h3><hr>
<!--                            <h1>--><?php //echo $_GET['xd']; ?><!--</h1>-->
                            <div class="form-inline">
                                <input type="text" class="under" name="answer" id="word" required="required" autocomplete="off" autofocus>
                                <button type="submit" name="send" value="1" class="btt">Dalej</button>
                                <p><?php echo $_GET['step']+1;?> z <?php echo count($array); ?></p>
                            </div>

                        </div>
                    </div>
                </form>
            </div>
        </div>
        <?php
    } else {
        $content = file_get_contents('answers.txt');
        $good = 0;
        $wrong = 0;

        $exp = explode('-', $content);
        foreach ($exp as $key => $value) {
            $spl = explode(':', $value);
            if (count($spl) == 2) {
                if($_GET['type']==1){
                    if ($array[$spl[0]]['en'] == $spl[1]) {
                        $good += 1;
                    } else {
                        $wrong += 1;
                    }
                } else {
                    if ($array[$spl[0]]['pl'] == $spl[1]) {
                        $good += 1;
                    } else {
                        $wrong += 1;
                    }
                }

            }
        }


        echo '<div class="well">';
        echo '<p>Poprawne odpowiedzi: <span class="badge badge-success">' . $good . '</span></p>';
        echo '<p>Niepoprawne odpowiedzi: <span class="badge badge-warning">' . $wrong . '</span></p>';
        echo '</div>';


        echo '<table class="table table-bordered">';
        echo '<thead>
           <tr>
            <th>Pytanie</th>
            <th>Odpowiedz</th>
            <th>Prawidłowa</th>
           </tr></thead><tbody>';

        foreach ($exp as $key => $value) {
            $spl = explode(':', $value);
            if (count($spl) == 2) {
                // $spl[0] -> numer pytania, $spl[1] -> odpowiedz

                if ($_GET['type'] == 1) {
                    if ($array[$spl[0]]['en'] == $spl[1]) {
                        echo '<tr class="success">';
                    } else {
                        echo '<tr class="warning">';
                    }
                    echo '<td>' . $array[$spl[0]]['pl'] . '</td>';
                    echo '<td>' . $spl[1] . '</td>';
                    echo '<td>' . $array[$spl[0]]['en'] . '</td>';
                    echo '</tr>';
                } else {
                    if (trim($array[$spl[0]]['pl']) == trim($spl[1])) {
                        echo '<tr class="success">';
                    } else {
                        echo '<tr class="warning">';
                    }
                    echo '<td>' . $array[$spl[0]]['en'] . '</td>';
                    echo '<td>' . $spl[1] . '</td>';
                    echo '<td>' . $array[$spl[0]]['pl'] . '</td>';
                    echo '</tr>';
                }
            }
        }

        echo '</tbody></table>'; ?>
            <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="GET">
                <input type="hidden" name="r" value="site/learn">
                <button type="submit" class="btn btn-lg btn-primary center-block" name="save" value="2">Zakończ naukę</button>
            </form>
            <?php
    }
}
?>