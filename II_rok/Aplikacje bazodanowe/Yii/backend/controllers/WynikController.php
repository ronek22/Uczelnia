<?php

namespace backend\controllers;

use Yii;
use backend\models\Wynik;
use backend\models\WynikSearch;
use backend\models\Konto;
use backend\models\Zestaw;
use yii\web\Controller;
use yii\web\NotFoundHttpException;
use yii\filters\VerbFilter;
use yii\helpers\ArrayHelper;

/**
 * WynikController implements the CRUD actions for Wynik model.
 */
class WynikController extends Controller
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
     * Lists all Wynik models.
     * @return mixed
     */
    public function actionIndex()
    {
        $searchModel = new WynikSearch();
        $dataProvider = $searchModel->search(Yii::$app->request->queryParams);

        return $this->render('index', [
            'searchModel' => $searchModel,
            'dataProvider' => $dataProvider,
        ]);
    }

    /**
     * Displays a single Wynik model.
     * @param integer $id
     * @return mixed
     */
    public function actionView($id)
    {
        return $this->render('view', [
            'model' => $this->findModel($id),
        ]);
    }

    /**
     * Creates a new Wynik model.
     * If creation is successful, the browser will be redirected to the 'view' page.
     * @return mixed
     */
    public function actionCreate()
    {
        $model = new Wynik();

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        $zestaw=Zestaw::find()
            ->orderBy('nazwa')
            ->all();
        $zestaw = ArrayHelper::map($zestaw,'id','nazwa');



        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'id' => $model->id]);
        } else {
            return $this->render('create', [
                'model' => $model,
                'konta' => $konta,
                'zestaw' => $zestaw,
            ]);
        }
    }

    /**
     * Updates an existing Wynik model.
     * If update is successful, the browser will be redirected to the 'view' page.
     * @param integer $id
     * @return mixed
     */
    public function actionUpdate($id)
    {
        $model = $this->findModel($id);

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        $zestaw=Zestaw::find()
            ->orderBy('nazwa')
            ->all();
        $zestaw = ArrayHelper::map($zestaw,'id','nazwa');

        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'id' => $model->id]);
        } else {
            return $this->render('update', [
                'model' => $model,
                'konta' => $konta,
                'zestaw' => $zestaw,
            ]);
        }
    }

    /**
     * Deletes an existing Wynik model.
     * If deletion is successful, the browser will be redirected to the 'index' page.
     * @param integer $id
     * @return mixed
     */
    public function actionDelete($id)
    {
        $this->findModel($id)->delete();

        return $this->redirect(['index']);
    }

    /**
     * Finds the Wynik model based on its primary key value.
     * If the model is not found, a 404 HTTP exception will be thrown.
     * @param integer $id
     * @return Wynik the loaded model
     * @throws NotFoundHttpException if the model cannot be found
     */
    protected function findModel($id)
    {
        if (($model = Wynik::findOne($id)) !== null) {
            return $model;
        } else {
            throw new NotFoundHttpException('The requested page does not exist.');
        }
    }
}
