<?php

/* @var $this yii\web\View */
/* @var $form yii\bootstrap\ActiveForm */
/* @var $model \common\models\LoginForm */

use yii\helpers\Html;
use yii\bootstrap\ActiveForm;

$this->title = 'Logowanie';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="site-login">
    <h1><?= Html::encode($this->title) ?></h1>

    <p>Wypełnij wszystkie pola, aby się zalogować:</p>

    <div class="row">
        <div class="col-lg-5">
            <?php $form = ActiveForm::begin(['id' => 'login-form']); ?>

                <?= $form->field($model, 'username')->textInput(['autofocus' => true]) -> label('Nazwa użytkownika'); ?>

                <?= $form->field($model, 'password')->passwordInput() ->label('Hasło'); ?>

                <?= $form->field($model, 'rememberMe')->checkbox(['label' => 'Zapamiętaj mnie']) ?>

                <div class="form-group">
                    <?= Html::submitButton('Zaloguj się', ['class' => 'btn btn-primary', 'name' => 'login-button']) ?>
                </div>

            <?php ActiveForm::end(); ?>
        </div>
    </div>

</div>
