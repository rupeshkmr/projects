from django.urls import  include, path
from .views import user_profile, UpdateUserProfile, ProfilePage, error, ConfirmProfile


urlpatterns = [
    path('user-profile/', user_profile, name='user-profile'),
    path('update-user-profile/<int:pk>/', UpdateUserProfile.as_view(), name='update-user-profile'),
    path('profile-page/', ProfilePage.as_view(), name='profile-page'),
    path('error/', error, name='error'),
    path('confirm-profile/', ConfirmProfile.as_view(), name='confirm-profile'),

]

