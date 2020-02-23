from django.urls import path
from .views import login_page,RegisterView,logout_page,ActivateAccount, change_password


urlpatterns = [
    path('login/', login_page, name='login'),
    path('register/', RegisterView.as_view(),name='register'),
    path('logout/', logout_page,name='logout'),
    path('activate_account/<int:pk>/', ActivateAccount.as_view(), name='activate_account'),
    path('change_password/', change_password, name='change_password'),

]

