#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Counter : public QObject
{
	Q_OBJECT
public:
	explicit Counter(QObject *parent = nullptr);

	int setValue(int value) const;
	void countFrom(int setValue, int delay);

private:
	QAtomicInt *m_counter;
	bool m_counting;

signals:
	void changed(int setValue);
};

#endif // WORKER_H
