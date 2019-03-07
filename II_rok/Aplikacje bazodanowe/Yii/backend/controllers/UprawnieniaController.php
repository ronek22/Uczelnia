<?php

namespace backend\controllers;

use Yii;
use backend\models\Uprawnienia;
use backend\models\Konto;
use backend\models\Podkategoria;
use backend\models\UprawnieniaSearch;
use yii\web\Controller;
use yii\web\NotFoundHttpException;
use yii\filters\VerbFilter;
use yii\helpers\ArrayHelper;

/**
 * UprawnieniaController implements the CRUD actions for Uprawnienia model.
 */
class UprawnieniaController extends Controller
{
    /**
     * @inheritdoc
     */
    public function behaviors()
    {
        return [
            'verbs' => [
                'class' => VerbFilter::className(),
                'actions' => [
                    'delete' => ['POST'],
                ],
            ],
        ];
    }

    /**
     * Lists all Uprawnienia models.
     * @return mixed
     */
    public function actionIndex()
    {
        $searchModel = new UprawnieniaSearch();
        $dataProvider = $searchModel->search(Yii::$app->request->queryParams);

        return $this->render('index', [
            'searchModel' => $searchModel,
            'dataProvider' => $dataProvider,
        ]);
    }

    /**
     * Displays a single Uprawnienia model.
     * @param integer $konto_id
     * @param integer $podkategoria_id
     * @return mixed
     */
    public function actionView($konto_id, $podkategoria_id)
    {
        return $this->render('view', [
            'model' => $this->findModel($konto_id, $podkategoria_id),
        ]);
    }

    /**
     * Creates a new Uprawnienia model.
     * If creation is successful, the browser will be redirected to the 'view' page.
     * @return mixed
     */
    public function actionCreate()
    {
        $model = new Uprawnienia();

        $podkategoria=Podkategoria::find()
            ->orderBy('nazwa')
            ->all();
        $podkategoria = ArrayHelper::map($podkategoria,'id','nazwa');

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'konto_id' => $model->konto_id, 'podkategoria_id' => $model->podkategoria_id]);
        } else {
            return $this->render('create', [
                'model' => $model,
                'podkategoria' => $podkategoria,
                'konta' => $konta,
            ]);
        }
    }

    /**
     * Updates an existing Uprawnienia model.
     * If update is successful, the browser will be redirected to the 'view' page.
     * @param integer $konto_id
     * @param integer $podkategoria_id
     * @return mixed
     */
    public function actionUpdate($konto_id, $podkategoria_id)
    {
        $model = $this->findModel($konto_id, $podkategoria_id);

        $podkategoria=Podkategoria::find()
            ->orderBy('nazwa')
            ->all();
        $podkategoria = ArrayHelper::map($podkategoria,'id','nazwa');

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'konto_id' => $model->konto_id, 'podkategoria_id' => $model->podkategoria_id]);
        } else {
            return $this->render('update', [
                'model' => $model,
                'podkategoria' => $podkategoria,
                'konta' => $konta,
            ]);
        }
    }

    /**
     * Deletes an existing Uprawnienia model.
     * If deletion is successful, the browser will be redirected to the 'index' page.
     * @param integer $konto_id
     * @param integer $podkategoria_id
     * @return mixed
     */
    public function actionDelete($konto_id, $podkategoria_id)
    {
        $this->findModel($konto_id, $podkategoria_id)->delete();

        return $this->redirect(['index']);
    }

    /**
     * Finds the Uprawnienia model based on its primary key value.
     * If the model is not found, a 404 HTTP exception will be thrown.
     * @param integer $konto_id
     * @param integer $podkategoria_id
     * @return Uprawnienia the loaded model
     * @throws NotFoundHttpException if the model cannot be found
     */
    protected function findModel($konto_id, $podkategoria_id)
    {
        if (($model = Uprawnienia::findOne(['konto_id' => $konto_id, 'podkategoria_id' => $podkategoria_id])) !== null) {
            return $model;
        } else {
            throw new NotFoundHttpException('The requested page does not exist.');
        }
    }
}
