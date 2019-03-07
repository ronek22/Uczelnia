<?php

namespace backend\models;

use Yii;
use yii\base\Model;
use yii\data\ActiveDataProvider;
use backend\models\Wynik;

/**
 * WynikSearch represents the model behind the search form about `backend\models\Wynik`.
 */
class WynikSearch extends Wynik
{
    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['id', 'konto_id', 'zestaw_id', 'wynik'], 'integer'],
            [['data_wyniku'], 'safe'],
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
        $query = Wynik::find();

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
            'id' => $this->id,
            'konto_id' => $this->konto_id,
            'zestaw_id' => $this->zestaw_id,
            'data_wyniku' => $this->data_wyniku,
            'wynik' => $this->wynik,
        ]);

        return $dataProvider;
    }
}
