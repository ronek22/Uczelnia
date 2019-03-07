<?php

use yii\helpers\Html;
use yii\grid\GridView;
use backend\models\Konto;
use yii\data\ActiveDataProvider;
use yii\db\Query;
/* @var $this yii\web\View */
/* @var $searchModel backend\models\ZestawSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Zestaw';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="zestaw-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <p>
        <?= Html::a('Utwórz Zestaw', ['create'], ['class' => 'btn btn-success']) ?>
    </p>

    <?php
    $role = Konto::getRole(Yii::$app -> user -> id) ->rola_id;
    if(1==$role){
     echo GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],

            //'id',
            'konto.username:text:Użytkownik',
            [
                'label' => 'Pierwszy język',
                'value' => function ($searchModel) {
                    $rows = (new \yii\db\Query())
                        ->select(['nazwa'])
                        ->from('jezyk')
                        ->where(['id' => $searchModel->jezyk1_id])
                        ->one();
                    return $rows['nazwa'];
                }
            ],
            [
                'label' => 'Drugi język',
                'value' => function ($searchModel) {
                    $rows = (new \yii\db\Query())
                        ->select(['nazwa'])
                        ->from('jezyk')
                        ->where(['id' => $searchModel->jezyk2_id])
                        ->one();
                    return $rows['nazwa'];
                }
            ],
            'podkategoria.nazwa:text:Podkategoria',
            'nazwa',
            [
                'label' => 'Zestaw',
                'format' => 'raw',
                'value' => function ($searchModel) {
                    $rows = (new \yii\db\Query())
                        ->select(['zestaw'])
                        ->from('zestaw')
                        ->where(['id' => $searchModel->id])
                        ->one();

                    $words = explode(PHP_EOL, $rows['zestaw']);
                    $words = array_map('trim', $words);

                    $ret = '<ul style="list-style: none;margin-left: -30px;">';
                    foreach ($words as $key => $value) {
                        $explode = explode(';', $value);
                        if (count($explode) == 2) {
                            $ret .= '<li>' . $explode[0] . ' - ' . $explode[1] . '</li>';
                        }
                    }

                    $ret .= '</ul>';
                    return $ret;
                }
            ],
            //'zestaw:ntext',
            'ilosc_slowek',
            'data_dodania',
            //'data_edycji',

            ['class' => 'yii\grid\ActionColumn'],
        ],
    ]);} else if(2==$role) { //SUPERREDAKTOR

        $rows = (new \yii\db\Query())
            ->select('z.id, z.nazwa, z.ilosc_slowek, z.data_dodania, z.jezyk1_id, z.jezyk2_id, z.zestaw, z.podkategoria_id,p.nazwa as podkat,z.konto_id,k.username')
            ->from('zestaw z')
            ->innerJoin('uprawnienia u', 'z.podkategoria_id = u.podkategoria_id')
            ->innerJoin('konto k', 'k.id=z.konto_id')
            ->innerJoin('podkategoria p', 'p.id=z.podkategoria_id')
            ->Where(['u.konto_id' => Yii::$app -> user -> id])
            ->all();


    ?>
    <table class="table table-striped table-bordered">
        <thead>
        <tr>
            <th>Nazwa</th>
            <th>Użytkownik</th>
            <th>Podkategoria</th>
            <th>Data dodania</th>
            <th>Pierwszy język</th>
            <th>Drugi język</th>
            <th>Słówka</th>
            <th>Edycja</th>
        </tr>
        </thead>
        <tbody>
        <?php
        for ($i = 0; $i < count($rows); $i++) {
            ?>
            <tr>
                <td><?= $rows[$i]['nazwa'] ?></td>
                <td><?= $rows[$i]['username'] ?></td>
                <td><?= $rows[$i]['podkat'] ?></td>
                <td><?= $rows[$i]['data_dodania'] ?></td>
                <td><?= (new \yii\db\Query())->select(['nazwa'])->from('jezyk')->where(['id' => $rows[$i]['jezyk1_id']])->one()['nazwa']; ?></td>
                <td><?= (new \yii\db\Query())->select(['nazwa'])->from('jezyk')->where(['id' => $rows[$i]['jezyk2_id']])->one()['nazwa']; ?></td>
                <td>
                    <button type="button" class="btn btn-primary btn-sm" data-toggle="modal" data-target="#myModal<?=$i;?>">Wyświetl</button>
                </td>
                <td>
                    <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fview&amp;id=<?= $rows[$i]['id'] ?>" title="Zobacz szczegóły" aria-label="Zobacz szczegóły" data-pjax="0"><span class="glyphicon glyphicon-eye-open"></span></a>
                    <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fupdate&amp;id=<?= $rows[$i]['id'] ?>" title="Aktualizuj" aria-label="Aktualizuj" data-pjax="0"><span class="glyphicon glyphicon-pencil"></span></a>
                    <?php
                    if ($rows[$i]['konto_id'] == Yii::$app -> user -> id) {
                        ?>
                        <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fdelete&amp;id=<?= $rows[$i]['id'] ?>" title="Usuń" aria-label="Usuń" data-pjax="0" data-confirm="Czy na pewno usunąć ten element?" data-method="post"><span class="glyphicon glyphicon-trash"></span></a>
                        <?php
                    }
                    ?>
                </td>
            </tr>
            <div class="modal fade" id="myModal<?=$i;?>" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
                <div class="modal-dialog" role="document">
                    <div class="modal-content">
                        <div class="modal-header">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span
                                        aria-hidden="true">&times;</span></button>
                            <h4 class="modal-title" id="myModalLabel">Zestaw słówek</h4>
                        </div>
                        <div class="modal-body">
                            <?php





                            $words = explode(PHP_EOL, $rows[$i]['zestaw']);
                            $words = array_map('trim', $words);
                            ?>
                            <ul>
                                <?php
                                foreach ($words as $key => $value) {
                                    $explode = explode(';', $value);
                                    if (count($explode) == 2) {
                                        echo '<li>' . $explode[0] . ' - ' . $explode[1] . '</li>';
                                    }
                                }
                                ?>
                            </ul>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-default" data-dismiss="modal">Zamknij</button>
                        </div>
                    </div>
                </div>
            </div>
            <?php
        }
        ?>
        </tbody>
    </table>
    <?php
    } else if($role==3){ //REDAKTOR
    $rows = (new \yii\db\Query())
        ->select('z.id, z.nazwa, z.ilosc_slowek, z.data_dodania, z.jezyk1_id, z.jezyk2_id, z.zestaw, z.podkategoria_id,p.nazwa as podkat,z.konto_id,k.username')
        ->from('zestaw z')
        ->innerJoin('uprawnienia u', 'z.podkategoria_id = u.podkategoria_id')
        ->innerJoin('konto k', 'k.id=z.konto_id')
        ->innerJoin('podkategoria p', 'p.id=z.podkategoria_id')
        ->Where(['z.konto_id' => Yii::$app -> user -> id])
        ->all();


    ?>
    <table class="table table-striped table-bordered">
        <thead>
        <tr>
            <th>Nazwa</th>
            <th>Użytkownik</th>
            <th>Podkategoria</th>
            <th>Data dodania</th>
            <th>Pierwszy język</th>
            <th>Drugi język</th>
            <th>Słówka</th>
            <th>Edycja</th>
        </tr>
        </thead>
        <tbody>
        <?php
        for ($i = 0; $i < count($rows); $i++) {
            ?>
            <tr>
                <td><?= $rows[$i]['nazwa'] ?></td>
                <td><?= $rows[$i]['username'] ?></td>
                <td><?= $rows[$i]['podkat'] ?></td>
                <td><?= $rows[$i]['data_dodania'] ?></td>
                <td><?= (new \yii\db\Query())->select(['nazwa'])->from('jezyk')->where(['id' => $rows[$i]['jezyk1_id']])->one()['nazwa']; ?></td>
                <td><?= (new \yii\db\Query())->select(['nazwa'])->from('jezyk')->where(['id' => $rows[$i]['jezyk2_id']])->one()['nazwa']; ?></td>
                <td>
                    <button type="button" class="btn btn-primary btn-sm" data-toggle="modal" data-target="#myModal<?=$i;?>">Wyświetl</button>
                </td>
                <td>
                    <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fview&amp;id=<?= $rows[$i]['id'] ?>" title="Zobacz szczegóły" aria-label="Zobacz szczegóły" data-pjax="0"><span class="glyphicon glyphicon-eye-open"></span></a>
                    <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fupdate&amp;id=<?= $rows[$i]['id'] ?>" title="Aktualizuj" aria-label="Aktualizuj" data-pjax="0"><span class="glyphicon glyphicon-pencil"></span></a>
                    <?php
                    if ($rows[$i]['konto_id'] == Yii::$app -> user -> id) {
                        ?>
                        <a href="/~jronkiewicz/advanced/backend/web/index.php?r=zestaw%2Fdelete&amp;id=<?= $rows[$i]['id'] ?>" title="Usuń" aria-label="Usuń" data-pjax="0" data-confirm="Czy na pewno usunąć ten element?" data-method="post"><span class="glyphicon glyphicon-trash"></span></a>
                        <?php
                    }
                    ?>
                </td>
            </tr>
            <div class="modal fade" id="myModal<?=$i;?>" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
                <div class="modal-dialog" role="document">
                    <div class="modal-content">
                        <div class="modal-header">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span
                                        aria-hidden="true">&times;</span></button>
                            <h4 class="modal-title" id="myModalLabel">Zestaw słówek</h4>
                        </div>
                        <div class="modal-body">
                            <?php





                            $words = explode(PHP_EOL, $rows[$i]['zestaw']);
                            $words = array_map('trim', $words);
                            ?>
                            <ul>
                                <?php
                                foreach ($words as $key => $value) {
                                    $explode = explode(';', $value);
                                    if (count($explode) == 2) {
                                        echo '<li>' . $explode[0] . ' - ' . $explode[1] . '</li>';
                                    }
                                }
                                ?>
                            </ul>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-default" data-dismiss="modal">Zamknij</button>
                        </div>
                    </div>
                </div>
            </div>
            <?php
        }
        ?>
        </tbody>
    </table>
    <?php }

    ?>
</div>
