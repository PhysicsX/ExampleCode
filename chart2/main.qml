import QtQuick 2.0
import QtCharts 2.0

ChartView {
    title: "Results"
    anchors.fill: parent
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    HorizontalStackedBarSeries {
        axisY: BarCategoryAxis { categories: ["Temp", "Sweat", "Heart", "Oxygen", "Health"] }
        BarSet { label: "Bob"; values: [22, 69, 37, 68, 78, 100] }

    }
}
