#include "Counter.h"
#include <QTimer>

Counter::Counter(QObject *parent) :
	QObject(parent),
	m_counter(new QAtomicInt()),
	m_counting(false)
{

}

int Counter::setValue(int value) const
{
	return m_counter->fetchAndStoreRelaxed(value);
}

void Counter::countFrom(int value, int delay)
{
	if (m_counting)
		return;

	m_counting = true;
	m_counter->store(value);

	auto *timer = new QTimer();

	timer->start(delay);

	connect(timer, &QTimer::timeout, [this](){
		m_counter->operator ++();
		changed(m_counter->load());
	});
}
