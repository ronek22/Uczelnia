<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel backend\models\WynikSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Wynik';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="wynik-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <p>
        <?= Html::a('Utwórz Wynik', ['create'], ['class' => 'btn btn-success']) ?>
    </p>
    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],

            //'id',
            'konto.username:text:Użytkownik',
            'zestaw.nazwa:text:Zestaw',
            'data_wyniku',
            'wynik',

            ['class' => 'yii\grid\ActionColumn'],
        ],
    ]); ?>
</div>
