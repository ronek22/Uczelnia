<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Konto */

$this->title = 'Utwórz konto';
$this->params['breadcrumbs'][] = ['label' => 'Konta', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="konto-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
