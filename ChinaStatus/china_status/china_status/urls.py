"""china_status URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
# from django.contrib import admin
# from django.urls import path, include
# from rest_framework import routers
# from province import views
#
# router = routers.DefaultRouter()
# router.register(r'resident_income', views.ResidentIncomeViewSet)
#
# urlpatterns = [
#     path(r'^', include(router.urls)),
#     path('grappelli/', include('grappelli.urls')),  # grappelli URLS
#
#     path('api-auth/', include('rest_framework.urls', namespace='rest_framework'))
# ]
from django.contrib import admin
from django.conf.urls import url, include
from django.urls import path
from rest_framework import routers
from province import views as province_views
from django.views.generic import TemplateView
router = routers.DefaultRouter()

router.register(r'province/resident_income', province_views.ResidentIncomeViewSet)

# Wire up our API using automatic URL routing.
# Additionally, we include login URLs for the browsable API.
urlpatterns = [
    url(r'^', include(router.urls)),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework')),
    url(r'^$', TemplateView.as_view(template_name="index.html")),
    path('admin/', admin.site.urls),
    path('grappelli/', include('grappelli.urls')),

]
