<?php

namespace backend\models;

use Yii;
use yii\base\Model;
use yii\data\ActiveDataProvider;
use backend\models\Zestaw;

/**
 * ZestawSearch represents the model behind the search form about `backend\models\Zestaw`.
 */
class ZestawSearch extends Zestaw
{
    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['id', 'konto_id', 'jezyk1_id', 'jezyk2_id', 'podkategoria_id', 'ilosc_slowek'], 'integer'],
            [['nazwa', 'zestaw', 'data_dodania', 'data_edycji'], 'safe'],
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
        $query = Zestaw::find();

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
            'jezyk1_id' => $this->jezyk1_id,
            'jezyk2_id' => $this->jezyk2_id,
            'podkategoria_id' => $this->podkategoria_id,
            'ilosc_slowek' => $this->ilosc_slowek,
            'data_dodania' => $this->data_dodania,
            'data_edycji' => $this->data_edycji,
        ]);

        $query->andFilterWhere(['like', 'nazwa', $this->nazwa])
            ->andFilterWhere(['like', 'zestaw', $this->zestaw]);

        return $dataProvider;
    }
}
