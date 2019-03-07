<?php

use yii\helpers\Html;
use yii\widgets\DetailView;

/* @var $this yii\web\View */
/* @var $model backend\models\Konto */

$this->title = 'Konto użytkownika '.$model->username;
$this->params['breadcrumbs'][] = ['label' => 'Konta', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="konto-view">

    <h1><?= Html::encode($this->title) ?></h1>

    <p>
        <?= Html::a('Aktualizuj', ['update', 'id' => $model->id], ['class' => 'btn btn-primary']) ?>
        <?= Html::a('Usuń', ['delete', 'id' => $model->id], [
            'class' => 'btn btn-danger',
            'data' => [
                'confirm' => 'Czy na pewno chcesz usunąć tego użytkownika?',
                'method' => 'post',
            ],
        ]);
        ?>
    </p>

    <?php echo DetailView::widget([
        'model' => $model,
        'attributes' => [
           // 'id',
            [
                'label' => 'Imię',
                'value' => $model->imie,
            ],
            'nazwisko',
            'email:email',
            [
                'label' => 'Login',
                'value' => $model->username,
            ],
            [
                'label' => 'Rola', //'roleName.nazwa',
                'value' => function($model) {
                    $rows = (new \yii\db\Query())
                        ->select(['nazwa'])
                        ->from('rola')
                        ->where(['id' => $model -> rola_id])
                        ->one();
                    return $rows['nazwa'];
                }
            ],
        ],
    ]) ?>

</div>
