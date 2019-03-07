<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel backend\models\RolaSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Rola';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="rola-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <p>
        <?= Html::a('Utwórz Role', ['create'], ['class' => 'btn btn-success']) ?>
    </p>
    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],

            //'id',
            'nazwa',
            'opis',

            ['class' => 'yii\grid\ActionColumn'],
        ],
    ]); ?>
</div>
