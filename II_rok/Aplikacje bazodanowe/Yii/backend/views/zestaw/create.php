<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Zestaw */

$this->title = 'Utwórz Zestaw';
$this->params['breadcrumbs'][] = ['label' => 'Zestaw', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="zestaw-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'podkategoria' => $podkategoria,
        'konta' => $konta,
        'jezyk' => $jezyk,
    ]) ?>

</div>
