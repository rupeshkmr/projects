from django.contrib import admin
from django.contrib.auth.models import Group
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin


from .forms import RegisterForm, UserAdminChangeForm
from .models import User

class UserAdmin(BaseUserAdmin):
    # The forms to add and change user instances
    change_form = RegisterForm#previously it was form and giving errors
    add_form = RegisterForm

    # The fields to be used in displaying the User model.
    # These override the definitions on the base UserAdmin
    # that reference specific fields on auth.User.
    list_display = ('email', 'admin')
    list_filter = ('admin',)
    fieldsets = (
        (None, {'fields': ('email', 'password','active','acc_on')}),
        # ('Personal info', {'fields': ()}),
        ('Permissions', {'fields': ('admin',)}),
    )
    # add_fieldsets is not a standard ModelAdmin attribute. UserAdmin
    # overrides get_fieldsets to use this attribute when creating a user.
    add_fieldsets = (
        (None, {
            'classes': ('wide',),
            'fields': ('email', 'password1', 'password2')}
        ),
    )
    search_fields = ('email',)
    ordering = ('email',)
    filter_horizontal = ()


admin.site.register(User, UserAdmin)
