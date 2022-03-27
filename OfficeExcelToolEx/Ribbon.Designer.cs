
namespace OfficeExcelToolEx
{
    partial class Ribbon : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public Ribbon()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.MeTable = this.Factory.CreateRibbonTab();
            this.MeGroupA = this.Factory.CreateRibbonGroup();
            this.button1 = this.Factory.CreateRibbonButton();
            this.MeTable.SuspendLayout();
            this.MeGroupA.SuspendLayout();
            this.SuspendLayout();
            // 
            // MeTable
            // 
            this.MeTable.ControlId.ControlIdType = Microsoft.Office.Tools.Ribbon.RibbonControlIdType.Office;
            this.MeTable.Groups.Add(this.MeGroupA);
            this.MeTable.Label = "TabAddIns";
            this.MeTable.Name = "MeTable";
            // 
            // MeGroupA
            // 
            this.MeGroupA.Items.Add(this.button1);
            this.MeGroupA.Label = "MeGroup";
            this.MeGroupA.Name = "MeGroupA";
            this.MeGroupA.Position = this.Factory.RibbonPosition.AfterOfficeId("");
            // 
            // button1
            // 
            this.button1.Label = "button1";
            this.button1.Name = "button1";
            this.button1.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.button1_Click);
            // 
            // Ribbon
            // 
            this.Name = "Ribbon";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.MeTable);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.Ribbon_Load);
            this.MeTable.ResumeLayout(false);
            this.MeTable.PerformLayout();
            this.MeGroupA.ResumeLayout(false);
            this.MeGroupA.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab MeTable;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup MeGroupA;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton button1;
    }

    partial class ThisRibbonCollection
    {
        internal Ribbon Ribbon
        {
            get { return this.GetRibbon<Ribbon>(); }
        }
    }
}
