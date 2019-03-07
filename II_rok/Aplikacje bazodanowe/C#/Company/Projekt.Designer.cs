namespace Company
{
    partial class Projekt
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.idprojektDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nazwaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.opisDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datastartuDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datakoncaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.budzetDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.projektBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.dataSet_baza = new Company.DataSet_baza();
            this.projektTableAdapter = new Company.DataSet_bazaTableAdapters.projektTableAdapter();
            this.txtNazwa = new System.Windows.Forms.TextBox();
            this.txtOpis = new System.Windows.Forms.TextBox();
            this.dateTimeStart = new System.Windows.Forms.DateTimePicker();
            this.dateTimeKon = new System.Windows.Forms.DateTimePicker();
            this.txtBudzet = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.btnInsert = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnUsun = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AutoGenerateColumns = false;
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idprojektDataGridViewTextBoxColumn,
            this.nazwaDataGridViewTextBoxColumn,
            this.opisDataGridViewTextBoxColumn,
            this.datastartuDataGridViewTextBoxColumn,
            this.datakoncaDataGridViewTextBoxColumn,
            this.budzetDataGridViewTextBoxColumn});
            this.dataGridView1.DataSource = this.projektBindingSource;
            this.dataGridView1.Location = new System.Drawing.Point(12, 12);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(618, 306);
            this.dataGridView1.TabIndex = 0;
            // 
            // idprojektDataGridViewTextBoxColumn
            // 
            this.idprojektDataGridViewTextBoxColumn.DataPropertyName = "id_projekt";
            this.idprojektDataGridViewTextBoxColumn.HeaderText = "id_projekt";
            this.idprojektDataGridViewTextBoxColumn.Name = "idprojektDataGridViewTextBoxColumn";
            this.idprojektDataGridViewTextBoxColumn.ReadOnly = true;
            this.idprojektDataGridViewTextBoxColumn.Visible = false;
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
            // datastartuDataGridViewTextBoxColumn
            // 
            this.datastartuDataGridViewTextBoxColumn.DataPropertyName = "data_startu";
            this.datastartuDataGridViewTextBoxColumn.HeaderText = "data_startu";
            this.datastartuDataGridViewTextBoxColumn.Name = "datastartuDataGridViewTextBoxColumn";
            // 
            // datakoncaDataGridViewTextBoxColumn
            // 
            this.datakoncaDataGridViewTextBoxColumn.DataPropertyName = "data_konca";
            this.datakoncaDataGridViewTextBoxColumn.HeaderText = "data_konca";
            this.datakoncaDataGridViewTextBoxColumn.Name = "datakoncaDataGridViewTextBoxColumn";
            // 
            // budzetDataGridViewTextBoxColumn
            // 
            this.budzetDataGridViewTextBoxColumn.DataPropertyName = "budzet";
            this.budzetDataGridViewTextBoxColumn.HeaderText = "budzet";
            this.budzetDataGridViewTextBoxColumn.Name = "budzetDataGridViewTextBoxColumn";
            // 
            // projektBindingSource
            // 
            this.projektBindingSource.DataMember = "projekt";
            this.projektBindingSource.DataSource = this.dataSet_baza;
            // 
            // dataSet_baza
            // 
            this.dataSet_baza.DataSetName = "DataSet_baza";
            this.dataSet_baza.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // projektTableAdapter
            // 
            this.projektTableAdapter.ClearBeforeFill = true;
            // 
            // txtNazwa
            // 
            this.txtNazwa.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.projektBindingSource, "nazwa", true));
            this.txtNazwa.Location = new System.Drawing.Point(709, 14);
            this.txtNazwa.Name = "txtNazwa";
            this.txtNazwa.Size = new System.Drawing.Size(159, 20);
            this.txtNazwa.TabIndex = 1;
            // 
            // txtOpis
            // 
            this.txtOpis.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.projektBindingSource, "opis", true));
            this.txtOpis.Location = new System.Drawing.Point(709, 41);
            this.txtOpis.Name = "txtOpis";
            this.txtOpis.Size = new System.Drawing.Size(159, 20);
            this.txtOpis.TabIndex = 2;
            // 
            // dateTimeStart
            // 
            this.dateTimeStart.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.projektBindingSource, "data_startu", true));
            this.dateTimeStart.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeStart.Location = new System.Drawing.Point(709, 68);
            this.dateTimeStart.Name = "dateTimeStart";
            this.dateTimeStart.Size = new System.Drawing.Size(159, 20);
            this.dateTimeStart.TabIndex = 3;
            // 
            // dateTimeKon
            // 
            this.dateTimeKon.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.projektBindingSource, "data_konca", true));
            this.dateTimeKon.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeKon.Location = new System.Drawing.Point(709, 95);
            this.dateTimeKon.Name = "dateTimeKon";
            this.dateTimeKon.Size = new System.Drawing.Size(159, 20);
            this.dateTimeKon.TabIndex = 4;
            // 
            // txtBudzet
            // 
            this.txtBudzet.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.projektBindingSource, "budzet", true, System.Windows.Forms.DataSourceUpdateMode.OnValidation, "0", "C2"));
            this.txtBudzet.Location = new System.Drawing.Point(709, 122);
            this.txtBudzet.Name = "txtBudzet";
            this.txtBudzet.Size = new System.Drawing.Size(159, 20);
            this.txtBudzet.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(637, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Nazwa";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(637, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(28, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Opis";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(637, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Data startu";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(637, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Data końca";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(637, 128);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Budżet";
            // 
            // btnInsert
            // 
            this.btnInsert.Location = new System.Drawing.Point(646, 270);
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.Size = new System.Drawing.Size(75, 23);
            this.btnInsert.TabIndex = 11;
            this.btnInsert.Text = "Dodaj";
            this.btnInsert.UseVisualStyleBackColor = true;
            this.btnInsert.Click += new System.EventHandler(this.btnInsert_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(728, 270);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 12;
            this.btnSave.Text = "Edytuj";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnUsun
            // 
            this.btnUsun.Location = new System.Drawing.Point(810, 269);
            this.btnUsun.Name = "btnUsun";
            this.btnUsun.Size = new System.Drawing.Size(75, 23);
            this.btnUsun.TabIndex = 13;
            this.btnUsun.Text = "Usuń";
            this.btnUsun.UseVisualStyleBackColor = true;
            this.btnUsun.Click += new System.EventHandler(this.btnUsun_Click);
            // 
            // Projekt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 330);
            this.Controls.Add(this.btnUsun);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnInsert);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtBudzet);
            this.Controls.Add(this.dateTimeKon);
            this.Controls.Add(this.dateTimeStart);
            this.Controls.Add(this.txtOpis);
            this.Controls.Add(this.txtNazwa);
            this.Controls.Add(this.dataGridView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Projekt";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Projekt";
            this.Load += new System.EventHandler(this.Projekt_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private DataSet_baza dataSet_baza;
        private System.Windows.Forms.BindingSource projektBindingSource;
        private DataSet_bazaTableAdapters.projektTableAdapter projektTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn idprojektDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nazwaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn opisDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datastartuDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datakoncaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn budzetDataGridViewTextBoxColumn;
        private System.Windows.Forms.TextBox txtNazwa;
        private System.Windows.Forms.TextBox txtOpis;
        private System.Windows.Forms.DateTimePicker dateTimeStart;
        private System.Windows.Forms.DateTimePicker dateTimeKon;
        private System.Windows.Forms.TextBox txtBudzet;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnUsun;
    }
}