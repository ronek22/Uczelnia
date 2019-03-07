<?php

use yii\helpers\Html;
use yii\widgets\DetailView;

/* @var $this yii\web\View */
/* @var $model backend\models\Zestaw */

$this->title = $model->nazwa;
$this->params['breadcrumbs'][] = ['label' => 'Zestaw', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="zestaw-view">

    <h1><?= Html::encode($this->title) ?></h1>

    <p>
        <?= Html::a('Zmień', ['update', 'id' => $model->id], ['class' => 'btn btn-primary']) ?>
        <?= Html::a('Usuń', ['delete', 'id' => $model->id], [
            'class' => 'btn btn-danger',
            'data' => [
                'confirm' => 'Jesteś pewny, że chcesz to usunąć?',
                'method' => 'post',
            ],
        ]) ?>
    </p>

    <?= DetailView::widget([
        'model' => $model,
        'attributes' => [
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
            'zestaw:ntext',
            'ilosc_slowek',
            'data_dodania',
            'data_edycji',
        ],
    ]) ?>

</div>
