<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel backend\models\JezykSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Jezyk';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="jezyk-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <p>
        <?= Html::a('Utwórz Jezyk', ['create'], ['class' => 'btn btn-success']) ?>
    </p>
    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],

//            'id',
            'nazwa',

            ['class' => 'yii\grid\ActionColumn'],
        ],
    ]); ?>
</div>
