#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	//QPushButton *pushButton1 = new QPushButton;
	//pushButton1->setObjectName("pushButton1");
	//QPushButton *pushButton2 = new QPushButton;
	//pushButton1->setObjectName("pushButton2");
	//QPushButton *pushButton3 = new QPushButton;
	//pushButton1->setObjectName("pushButton3");

	ui.setupUi(this);

	//connect(pushButton1, &QPushButton::clicked, this, &Widget::ChangeSinOffset);
	//connect(pushButton2, &QPushButton::clicked, this, &Widget::ChangeAmplitude);
	//connect(pushButton3, &QPushButton::clicked, this, &Widget::ChangeCycle);	

}

Widget::~Widget()
{

}

/**************************************************************************
Function Name:   InitSinGrid
Description:     初始化网格
**************************************************************************/
void Widget::InitSinGrid()
{

	m_FHRQwtPlot = new QwtPlot(this);
	m_FHRQwtPlot->move(10, 5);
	m_FHRQwtPlot->setFixedWidth(780);    // 设置坐标轴的大小
	m_FHRQwtPlot->setFixedHeight(210);
	m_FHRQwtPlot->setTitle(" ");         // 设置坐标轴的标题
	m_FHRQwtPlot->setAxisScale(QwtPlot::yLeft, 30, 240, 30); // 坐标轴的范围和间隔
	m_FHRQwtPlot->setAxisScale(QwtPlot::yRight, 30, 240, 30);
	m_FHRQwtPlot->setAxisScale(QwtPlot::xBottom, 0, 100, 20);
	m_FHRQwtPlot->enableAxis(QwtPlot::yRight, true);
	m_FHRQwtPlot->enableAxis(QwtPlot::xBottom, false);  // 隐藏X轴
	m_FHRQwtPlot->setStyleSheet("background:transparent;");//删除坐标轴背景
	m_FHRQwtPlot->setAxisMaxMinor(QwtPlot::xBottom, 4);
	m_FHRQwtPlot->setAxisMaxMinor(QwtPlot::yLeft, 3);//设置每一个大格有都少个小格
	m_FHRQwtPlot->setAxisMaxMinor(QwtPlot::yRight, 3);
	m_FHRQwtPlot->setAxisScaleDraw(QwtPlot::xBottom, new TimeScaleDraw(QDateTime::currentDateTime()));// 横坐标显示当前时间(需要把X轴显示出来，才能显示出时间)
	m_FHRQwtPlot->setCanvasBackground(Qt::white); // 设置背景白色

												  // 删除坐标轴间的间距
	for (int n = 0; n < m_FHRQwtPlot->axisCnt; n++)
	{
		QwtScaleWidget *poScaleWidget = m_FHRQwtPlot->axisWidget(n);
		if (poScaleWidget)
		{
			poScaleWidget->setMargin(0);
		}

		QwtScaleDraw *poScaleDraw = m_FHRQwtPlot->axisScaleDraw(n);
		if (poScaleDraw)
		{
			poScaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
		}
	}
	m_FHRQwtPlot->plotLayout()->setAlignCanvasToScales(true);

	//画网格
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->enableXMin(true);
	grid->enableYMin(true);
	grid->enableX(true);
	grid->enableY(true);
	grid->setMajorPen(QPen(Qt::gray, 1, Qt::SolidLine));  // 大网格
	grid->setMinorPen(QPen(QColor(186, 186, 186), 0, Qt::DotLine));// 小网格
	grid->attach(m_FHRQwtPlot);

	// 往坐标系添加曲线
	m_FHRCurve = new QwtPlotCurve;
	m_FHRCurve->setPen(QColor(255, 85, 255), 2, Qt::SolidLine);
	m_FHRCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);   //圆滑显示曲线
	m_FHRCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
	m_FHRCurve->attach(m_FHRQwtPlot);  // 把曲线加载到坐标轴上

									   //m_UpdateFlag = 0;

									   //m_LimitBackGroud = new Background(m_HighLimit,m_LowLimit);//给绘图填充背景
									   //m_LimitBackGroud->attach( m_FHRQwtPlot );//插入plot
									   // 启动定时器
	m_SinTimer = new QTimer();
	connect(m_SinTimer, SIGNAL(timeout()), this, SLOT(TimeSlot()));
	StartSin();   // 开始启动线程，产生Sin坐标点(上面SinData.h里面的接口函数)
	m_SinTimer->start(500);//0.5秒触发定时器

}



/**************************************************************************
Function Name:   TimeSlot
Description:     定时器槽函数，用来绘制Sin图像
**************************************************************************/
void Widget::TimeSlot()
{
	static int s_BeginAixsX = 0;  // 起始横坐标
	static int s_Result;

	if ((s_Result = GetSinData(&m_SinPointX, &m_SinPointY)) <= 0)  // 获取Sin坐标点
	{
		return;// 获取失败，直接返回
	}

	if (m_SinPointX >= 100)  // 当当前坐标轴画满了，就把坐标轴往前移动，(更新X轴范围)
	{
		s_BeginAixsX++;
		m_FHRQwtPlot->setAxisScale(QwtPlot::xBottom, s_BeginAixsX, m_SinPointX, 20);// 更新坐标轴
		m_DataVectorX.erase(m_DataVectorX.begin(), m_DataVectorX.begin() + 1);
		m_DataVectorY.erase(m_DataVectorY.begin(), m_DataVectorY.begin() + 1);
	}

	m_DataVectorX.append((double)m_SinPointX);
	m_DataVectorY.append((double)m_SinPointY);
	m_FHRCurve->setSamples(m_DataVectorX, m_DataVectorY);  // 绘图

	m_FHRQwtPlot->replot();  // 重绘，一定要调用否则没效果
}

//更改sin图像的Y轴偏移量、振幅、周期的槽函数。

void Widget::ChangeSinOffset()
{
	m_UpdateFlag = DATA_UPDATA;
	static int s_SinOffset = 120;
	if (s_SinOffset == 160)
		s_SinOffset = 120;
	s_SinOffset += 10;
	SetSinOffset(s_SinOffset);
	UpdateData();
}

void Widget::ChangeAmplitude()
{

	static int s_SinAmplitude = 20;
	if (s_SinAmplitude == 50)
		s_SinAmplitude = 20;
	m_UpdateFlag = DATA_UPDATA;

	s_SinAmplitude += 5;
	SetAmplitude(s_SinAmplitude);
	UpdateData();

}

void Widget::ChangeCycle()
{
	static int s_SinCycle = 4;
	if (s_SinCycle == 10)
		s_SinCycle = 4;
	m_UpdateFlag = DATA_UPDATA;

	s_SinCycle += 1;
	SetCycle(s_SinCycle);
	UpdateData();
}

/**************************************************************************/
//Function Name:     updateData
//Description:     更新sin图形的坐标，重绘
/**************************************************************************/
void Widget::UpdateData()
{
	//int axisX[m_SinPointX];
	//int axisY[m_SinPointX];
	int *axisX = new int[m_SinPointX];
	int *axisY = new int[m_SinPointX];
	UpdateSinData(axisX, axisY);  // SinData.h的接口函数
	m_DataVectorX.clear();
	m_DataVectorY.clear();
	for (int n = 0; n <m_SinPointX; n++)
	{
		m_DataVectorX.append((double)axisX[n]);
		m_DataVectorY.append((double)axisY[n]);
	}

	if (m_SinPointX >100)
	{
		int len = m_DataVectorX.length() - 100;
		if (len < 0)
			len = 0 - len;
		//m_FHRQwtPlot->setAxisScale(QwtPlot::xBottom,len,m_SinPointX,20);
		m_DataVectorX.erase(m_DataVectorX.begin(), m_DataVectorX.begin() + len);
		m_DataVectorY.erase(m_DataVectorY.begin(), m_DataVectorY.begin() + len);
	}

	m_FHRCurve->setSamples(m_DataVectorX, m_DataVectorY);
	m_FHRQwtPlot->replot();
	m_UpdateFlag = 0;
}