from django.contrib import admin
from django.urls import path, include
from django.conf import settings
from django.conf.urls.static import static
from .views import home_page
urlpatterns = [
    path('admin/', admin.site.urls),
    path('', home_page,name='home'),
    path('accounts/', include(('accounts.urls','accounts'),namespace='accounts')),
    path('profile/', include(('profile.urls','profile'),namespace='profile')),
    path('bank/', include(('bank.urls','bank'),namespace='bank')),

]
