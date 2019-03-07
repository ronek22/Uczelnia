<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Jezyk */

$this->title = 'Create Jezyk';
$this->params['breadcrumbs'][] = ['label' => 'Jezyks', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="jezyk-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
