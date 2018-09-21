#ifndef WIDGET_H
#define WIDGET_H

extern "C" {
#include "SinData.h"     // 表示需要使用到C中的头文件
}


#include <QtWidgets/QWidget>
#include "ui_widget.h"
//#include "SinData.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qdatetime.h>
#include <qwt_abstract_scale_draw.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qtimer.h>
#include <qvector.h>
#include <qpushbutton.h>


class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

	int m_UpdateFlag = 0;
	int DATA_UPDATA = 1;
	QVector<double> m_DataVectorX;
	QVector<double> m_DataVectorY;
	int m_SinPointX;
	int m_SinPointY;

	QwtPlot *m_FHRQwtPlot;
    QwtPlotCurve *m_FHRCurve;
    QTimer *m_SinTimer;
	QPushButton *pushButton1;
	QPushButton *pushButton2;
	QPushButton *pushButton3;

	void InitSinGrid();

	void UpdateData();

private:
	Ui::WidgetClass ui;

private slots:
	void ChangeSinOffset();
	void ChangeAmplitude();
	void ChangeCycle();
	void TimeSlot();

};

//时间坐标轴
class TimeScaleDraw : public QwtScaleDraw
{
public:
	TimeScaleDraw(const QDateTime &base) :
		baseTime(base) {

	}
	virtual QwtText label(double v) const
	{
		QDateTime upTime = baseTime.addSecs((int)v);
		return upTime.toString("yyyy-MM-dd\nhh:mm:ss");
	}
private:
	QDateTime baseTime;
};

#endif // WIDGET_H
