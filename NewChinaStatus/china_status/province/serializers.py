from rest_framework import serializers
from .models import ResidentIncome

class ResidentIncomeSerializer(serializers.ModelSerializer):
    class Meta:
        model = ResidentIncome
        fields = '__all__'
        # fields = ('url', 'username', 'email', 'groups')