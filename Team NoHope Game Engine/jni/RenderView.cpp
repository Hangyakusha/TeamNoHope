#include "RenderView.h"

using namespace gg;

RenderView::RenderView() {}
RenderView::~RenderView() {}

void RenderView::draw(Entity& entity)
{
	entity.draw();
}

void RenderView::display()
{

}

void RenderView::clear(const Color& color)
{

}