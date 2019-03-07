<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Podkategoria */

$this->title = 'Dodaj podkategorie';
$this->params['breadcrumbs'][] = ['label' => 'Podkategoria', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="podkategoria-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'kategorie' => $kategorie,
    ]) ?>

</div>
