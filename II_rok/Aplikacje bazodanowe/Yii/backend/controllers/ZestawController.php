<?php

namespace backend\controllers;

use Yii;
use backend\models\Zestaw;
use backend\models\Konto;
use backend\models\Jezyk;
use backend\models\Podkategoria;
use backend\models\ZestawSearch;
use yii\web\Controller;
use yii\web\NotFoundHttpException;
use yii\filters\VerbFilter;
use yii\helpers\ArrayHelper;
/**
 * ZestawController implements the CRUD actions for Zestaw model.
 */
class ZestawController extends Controller
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
     * Lists all Zestaw models.
     * @return mixed
     */
    public function actionIndex()
    {
        $searchModel = new ZestawSearch();
        $dataProvider = $searchModel->search(Yii::$app->request->queryParams);

        return $this->render('index', [
            'searchModel' => $searchModel,
            'dataProvider' => $dataProvider,
        ]);
    }

    /**
     * Displays a single Zestaw model.
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
     * Creates a new Zestaw model.
     * If creation is successful, the browser will be redirected to the 'view' page.
     * @return mixed
     */
    public function actionCreate()
    {
        $model = new Zestaw();

        $podkategoria=Podkategoria::find()
            ->orderBy('nazwa')
            ->all();
        $podkategoria = ArrayHelper::map($podkategoria,'id','nazwa');

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        $jezyk=Jezyk::find()
            ->orderBy('nazwa')
            ->all();
        $jezyk = ArrayHelper::map($jezyk,'id','nazwa');



        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'id' => $model->id]);
        } else {
            return $this->render('create', [
                'model' => $model,
                'podkategoria' => $podkategoria,
                'konta' => $konta,
                'jezyk' => $jezyk,
            ]);
        }
    }

    /**
     * Updates an existing Zestaw model.
     * If update is successful, the browser will be redirected to the 'view' page.
     * @param integer $id
     * @return mixed
     */
    public function actionUpdate($id)
    {
        $model = $this->findModel($id);

        $podkategoria=Podkategoria::find()
            ->orderBy('nazwa')
            ->all();
        $podkategoria = ArrayHelper::map($podkategoria,'id','nazwa');

        $konta=Konto::find()
            ->orderBy('username')
            ->all();
        $konta = ArrayHelper::map($konta,'id','username');

        $jezyk=Jezyk::find()
            ->orderBy('nazwa')
            ->all();
        $jezyk = ArrayHelper::map($jezyk,'id','nazwa');

        if ($model->load(Yii::$app->request->post()) && $model->save()) {
            return $this->redirect(['view', 'id' => $model->id]);
        } else {
            return $this->render('update', [
                'model' => $model,
                'podkategoria' => $podkategoria,
                'konta' => $konta,
                'jezyk' => $jezyk,
            ]);
        }
    }

    /**
     * Deletes an existing Zestaw model.
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
     * Finds the Zestaw model based on its primary key value.
     * If the model is not found, a 404 HTTP exception will be thrown.
     * @param integer $id
     * @return Zestaw the loaded model
     * @throws NotFoundHttpException if the model cannot be found
     */
    protected function findModel($id)
    {
        if (($model = Zestaw::findOne($id)) !== null) {
            return $model;
        } else {
            throw new NotFoundHttpException('The requested page does not exist.');
        }
    }
}
