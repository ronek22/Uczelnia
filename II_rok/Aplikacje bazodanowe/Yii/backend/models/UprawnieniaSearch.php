<?php

namespace backend\models;

use Yii;
use yii\base\Model;
use yii\data\ActiveDataProvider;
use backend\models\Uprawnienia;

/**
 * UprawnieniaSearch represents the model behind the search form about `backend\models\Uprawnienia`.
 */
class UprawnieniaSearch extends Uprawnienia
{
    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['konto_id', 'podkategoria_id'], 'integer'],
        ];
    }

    /**
     * @inheritdoc
     */
    public function scenarios()
    {
        // bypass scenarios() implementation in the parent class
        return Model::scenarios();
    }

    /**
     * Creates data provider instance with search query applied
     *
     * @param array $params
     *
     * @return ActiveDataProvider
     */
    public function search($params)
    {
        $query = Uprawnienia::find();

        // add conditions that should always apply here

        $dataProvider = new ActiveDataProvider([
            'query' => $query,
        ]);

        $this->load($params);

        if (!$this->validate()) {
            // uncomment the following line if you do not want to return any records when validation fails
            // $query->where('0=1');
            return $dataProvider;
        }

        // grid filtering conditions
        $query->andFilterWhere([
            'konto_id' => $this->konto_id,
            'podkategoria_id' => $this->podkategoria_id,
        ]);

        return $dataProvider;
    }
}
