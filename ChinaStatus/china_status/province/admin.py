from django.contrib import admin

# Register your models here.
from .models import ResidentIncome

class ResidentIncomeAdmin(admin.ModelAdmin):
    # list_display=('id', 'province', 'total', 'total_increase_rate',
    #               'city', 'city_increase_rate',
    #               'rural', 'rural_increase_rate',
    #               'total_increase', 'city_increase', 'rural_increase', 'year')
    list_display = [field.name for field in ResidentIncome._meta.fields]
    readonly_fields = [field.name for field in ResidentIncome._meta.fields]
    actions = None

    def has_add_permission(self, request):
        return False

    def has_delete_permission(self, request, obj=None):
        return False

admin.site.register(ResidentIncome, ResidentIncomeAdmin)