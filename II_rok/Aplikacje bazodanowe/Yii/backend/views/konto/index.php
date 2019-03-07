<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel backend\models\KontoSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Konta';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="konto-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <p>
       <!-- <?= Html::a('Utworz konto', ['create'], ['class' => 'btn btn-success']) ?> -->
    </p>
    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],
            //'id',
            'imie',
            'nazwisko',
            'email:email',
            [
                'label' => 'Login',
                'value' => 'username'
            ],
            [
                'label' => 'Status', //'roleName.nazwa',
                'value' => function($searchModel) {
                    if ($searchModel -> status == 10) {
                        return 'Aktywny';
                    } else {
                        return 'Nieaktywny';
                    }
                }
            ],
            [
                'label' => 'Rola', //'roleName.nazwa',
                'value' => function($searchModel) {
                    $rows = (new \yii\db\Query())
                        ->select(['nazwa'])
                        ->from('rola')
                        ->where(['id' => $searchModel -> rola_id])
                        ->one();
                    return $rows['nazwa'];
                }
            ],

            ['class' => 'yii\grid\ActionColumn'],
        ],
    ]); ?>
</div>
