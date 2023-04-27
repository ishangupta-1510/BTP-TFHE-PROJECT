"""textutils URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
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
from django.contrib import admin
from django.urls import path
from . import views
urlpatterns = [
    path('admin/', admin.site.urls),
    path('',views.index, name="index"),
    path('adminP',views.adminP, name="adminP"),
    path('upload',views.upload, name="upload"),
    path('output',views.output, name="output"),
    path('query',views.query, name="query"),
    path('select',views.select, name="select"),
    path('update',views.update, name="update"),
    path('result',views.result, name="result"),
    path('result_cust',views.result_cust, name="result_cust"),
    path('analyze1',views.analyze1, name="analyze1"),
    path('result1',views.result1, name="result1"),
    path('welcome',views.welcome, name="welcome"),
    path('analyze',views.analyze, name="analyze"),
    path('emp',views.emp, name="emp"),
    path('like',views.like, name="like"),
    path('selection',views.selection, name="selection"),
    path('mk_select',views.mk_select, name="mk_select"),
    path('mk_query',views.mk_query, name="mk_query"),
    path('mk_result',views.mk_result, name="mk_result")
]
