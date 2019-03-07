namespace Company
{
    partial class Stanowisko
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.dataGridViewStanowisko = new System.Windows.Forms.DataGridView();
            this.idstanowiskoDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nazwaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.opisDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dolnaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gornaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datadodaniaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.stanowiskoBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.dataSet_baza = new Company.DataSet_baza();
            this.stanowiskoTableAdapter = new Company.DataSet_bazaTableAdapters.stanowiskoTableAdapter();
            this.txtNazwa = new System.Windows.Forms.TextBox();
            this.txtOpis = new System.Windows.Forms.TextBox();
            this.txtDolna = new System.Windows.Forms.TextBox();
            this.txtGorna = new System.Windows.Forms.TextBox();
            this.Nazwa = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.dateTimeDod = new System.Windows.Forms.DateTimePicker();
            this.btnInsert = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnUsun = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewStanowisko)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewStanowisko
            // 
            this.dataGridViewStanowisko.AllowUserToAddRows = false;
            this.dataGridViewStanowisko.AutoGenerateColumns = false;
            this.dataGridViewStanowisko.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewStanowisko.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewStanowisko.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idstanowiskoDataGridViewTextBoxColumn,
            this.nazwaDataGridViewTextBoxColumn,
            this.opisDataGridViewTextBoxColumn,
            this.dolnaDataGridViewTextBoxColumn,
            this.gornaDataGridViewTextBoxColumn,
            this.datadodaniaDataGridViewTextBoxColumn});
            this.dataGridViewStanowisko.DataSource = this.stanowiskoBindingSource;
            this.dataGridViewStanowisko.Location = new System.Drawing.Point(12, 12);
            this.dataGridViewStanowisko.Name = "dataGridViewStanowisko";
            this.dataGridViewStanowisko.Size = new System.Drawing.Size(618, 306);
            this.dataGridViewStanowisko.TabIndex = 0;
            // 
            // idstanowiskoDataGridViewTextBoxColumn
            // 
            this.idstanowiskoDataGridViewTextBoxColumn.DataPropertyName = "id_stanowisko";
            this.idstanowiskoDataGridViewTextBoxColumn.HeaderText = "id_stanowisko";
            this.idstanowiskoDataGridViewTextBoxColumn.Name = "idstanowiskoDataGridViewTextBoxColumn";
            this.idstanowiskoDataGridViewTextBoxColumn.ReadOnly = true;
            this.idstanowiskoDataGridViewTextBoxColumn.Visible = false;
            // 
            // nazwaDataGridViewTextBoxColumn
            // 
            this.nazwaDataGridViewTextBoxColumn.DataPropertyName = "nazwa";
            this.nazwaDataGridViewTextBoxColumn.HeaderText = "nazwa";
            this.nazwaDataGridViewTextBoxColumn.Name = "nazwaDataGridViewTextBoxColumn";
            // 
            // opisDataGridViewTextBoxColumn
            // 
            this.opisDataGridViewTextBoxColumn.DataPropertyName = "opis";
            this.opisDataGridViewTextBoxColumn.HeaderText = "opis";
            this.opisDataGridViewTextBoxColumn.Name = "opisDataGridViewTextBoxColumn";
            // 
            // dolnaDataGridViewTextBoxColumn
            // 
            this.dolnaDataGridViewTextBoxColumn.DataPropertyName = "dolna";
            this.dolnaDataGridViewTextBoxColumn.HeaderText = "dolna";
            this.dolnaDataGridViewTextBoxColumn.Name = "dolnaDataGridViewTextBoxColumn";
            // 
            // gornaDataGridViewTextBoxColumn
            // 
            this.gornaDataGridViewTextBoxColumn.DataPropertyName = "gorna";
            this.gornaDataGridViewTextBoxColumn.HeaderText = "gorna";
            this.gornaDataGridViewTextBoxColumn.Name = "gornaDataGridViewTextBoxColumn";
            // 
            // datadodaniaDataGridViewTextBoxColumn
            // 
            this.datadodaniaDataGridViewTextBoxColumn.DataPropertyName = "data_dodania";
            this.datadodaniaDataGridViewTextBoxColumn.HeaderText = "data_dodania";
            this.datadodaniaDataGridViewTextBoxColumn.Name = "datadodaniaDataGridViewTextBoxColumn";
            // 
            // stanowiskoBindingSource
            // 
            this.stanowiskoBindingSource.DataMember = "stanowisko";
            this.stanowiskoBindingSource.DataSource = this.dataSet_baza;
            // 
            // dataSet_baza
            // 
            this.dataSet_baza.DataSetName = "DataSet_baza";
            this.dataSet_baza.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // stanowiskoTableAdapter
            // 
            this.stanowiskoTableAdapter.ClearBeforeFill = true;
            // 
            // txtNazwa
            // 
            this.txtNazwa.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.stanowiskoBindingSource, "nazwa", true));
            this.txtNazwa.Location = new System.Drawing.Point(709, 14);
            this.txtNazwa.Name = "txtNazwa";
            this.txtNazwa.Size = new System.Drawing.Size(159, 20);
            this.txtNazwa.TabIndex = 1;
            // 
            // txtOpis
            // 
            this.txtOpis.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.stanowiskoBindingSource, "opis", true));
            this.txtOpis.Location = new System.Drawing.Point(709, 41);
            this.txtOpis.Name = "txtOpis";
            this.txtOpis.Size = new System.Drawing.Size(159, 20);
            this.txtOpis.TabIndex = 2;
            // 
            // txtDolna
            // 
            this.txtDolna.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.stanowiskoBindingSource, "dolna", true, System.Windows.Forms.DataSourceUpdateMode.OnValidation, "0", "C2"));
            this.txtDolna.Location = new System.Drawing.Point(709, 68);
            this.txtDolna.Name = "txtDolna";
            this.txtDolna.Size = new System.Drawing.Size(159, 20);
            this.txtDolna.TabIndex = 3;
            // 
            // txtGorna
            // 
            this.txtGorna.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.stanowiskoBindingSource, "gorna", true, System.Windows.Forms.DataSourceUpdateMode.OnValidation, "0", "C2"));
            this.txtGorna.Location = new System.Drawing.Point(709, 95);
            this.txtGorna.Name = "txtGorna";
            this.txtGorna.Size = new System.Drawing.Size(159, 20);
            this.txtGorna.TabIndex = 4;
            // 
            // Nazwa
            // 
            this.Nazwa.AutoSize = true;
            this.Nazwa.Location = new System.Drawing.Point(636, 21);
            this.Nazwa.Name = "Nazwa";
            this.Nazwa.Size = new System.Drawing.Size(40, 13);
            this.Nazwa.TabIndex = 6;
            this.Nazwa.Text = "Nazwa";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(636, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Opis";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(636, 75);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Dolna";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(637, 101);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Górna";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(636, 129);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Data dod";
            // 
            // dateTimeDod
            // 
            this.dateTimeDod.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.stanowiskoBindingSource, "data_dodania", true));
            this.dateTimeDod.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeDod.Location = new System.Drawing.Point(709, 121);
            this.dateTimeDod.Name = "dateTimeDod";
            this.dateTimeDod.Size = new System.Drawing.Size(159, 20);
            this.dateTimeDod.TabIndex = 11;
            // 
            // btnInsert
            // 
            this.btnInsert.Location = new System.Drawing.Point(646, 270);
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.Size = new System.Drawing.Size(75, 23);
            this.btnInsert.TabIndex = 12;
            this.btnInsert.Text = "Dodaj";
            this.btnInsert.UseVisualStyleBackColor = true;
            this.btnInsert.Click += new System.EventHandler(this.btnInsert_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(727, 270);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 13;
            this.btnSave.Text = "Edytuj";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnUsun
            // 
            this.btnUsun.Location = new System.Drawing.Point(808, 270);
            this.btnUsun.Name = "btnUsun";
            this.btnUsun.Size = new System.Drawing.Size(75, 23);
            this.btnUsun.TabIndex = 14;
            this.btnUsun.Text = "Usuń";
            this.btnUsun.UseVisualStyleBackColor = true;
            this.btnUsun.Click += new System.EventHandler(this.btnUsun_Click);
            // 
            // Stanowisko
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 330);
            this.Controls.Add(this.btnUsun);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnInsert);
            this.Controls.Add(this.dateTimeDod);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Nazwa);
            this.Controls.Add(this.txtGorna);
            this.Controls.Add(this.txtDolna);
            this.Controls.Add(this.txtOpis);
            this.Controls.Add(this.txtNazwa);
            this.Controls.Add(this.dataGridViewStanowisko);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Stanowisko";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Stanowisko";
            this.Load += new System.EventHandler(this.Stanowisko_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewStanowisko)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewStanowisko;
        private DataSet_baza dataSet_baza;
        private System.Windows.Forms.BindingSource stanowiskoBindingSource;
        private DataSet_bazaTableAdapters.stanowiskoTableAdapter stanowiskoTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn idstanowiskoDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nazwaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn opisDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn dolnaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn gornaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datadodaniaDataGridViewTextBoxColumn;
        private System.Windows.Forms.TextBox txtNazwa;
        private System.Windows.Forms.TextBox txtOpis;
        private System.Windows.Forms.TextBox txtDolna;
        private System.Windows.Forms.TextBox txtGorna;
        private System.Windows.Forms.Label Nazwa;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DateTimePicker dateTimeDod;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnUsun;
    }
}